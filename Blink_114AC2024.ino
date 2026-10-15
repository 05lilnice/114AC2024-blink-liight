const int buttonPin = 2;    // 按鈕接腳
const int redPin = 9;       // 紅光 PWM 接腳
const int greenPin = 10;    // 綠光 PWM 接腳
const int bluePin = 11;     // 藍光 PWM 接腳

int colorMode = 0;            // 記錄目前的顏色模式 (0: 關閉, 1~6: 不同的固定顏色)
bool lastButtonState = HIGH;  // 上一次按鈕讀數
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50; // 防彈跳延遲毫秒數

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // 啟用內部上拉電阻
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // 1. 讀取按鈕狀態並處理點擊切換
  int reading = digitalRead(buttonPin);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    static int actualButtonState = HIGH;
    if (reading != actualButtonState) {
      actualButtonState = reading;
      // 當按鈕被按下（從 HIGH 變 LOW）時，切換下一個顏色模式
      if (actualButtonState == LOW) {
        colorMode = (colorMode + 1) % 7; // 總共有 0~6 種狀態循環
      }
    }
  }
  lastButtonState = reading;

  // 2. 根據不同的 colorMode 輸出對應的顏色
  // 提示：如果你使用的是共陽極模組，請將下方數值用 255 減去（例如 255 - 255 = 0）
  switch (colorMode) {
    case 0: // 關閉
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      break;
    case 1: // 紅色
      analogWrite(redPin, 255);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);
      break;
    case 2: // 綠色
      analogWrite(redPin, 0);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 0);
      break;
    case 3: // 藍色
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 255);
      break;
    case 4: // 黃色
      analogWrite(redPin, 255);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 0);
      break;
    case 5: // 紫色
      analogWrite(redPin, 255);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 255);
      break;
    case 6: // 白光
      analogWrite(redPin, 255);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 255);
      break;
  }
}