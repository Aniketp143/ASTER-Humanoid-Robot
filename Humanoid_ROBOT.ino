#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi.h>
#include <WebServer.h>

// ================= WiFi Configuration =================
const char* WIFI_SSID = "Aniket";
const char* WIFI_PASS = "00000000";

// ================= PCA9685 Configuration =================
#define PCA_ADDR   0x40
#define SERVOMIN   150
#define SERVOMAX   600
#define SERVO_FREQ 50

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PCA_ADDR);

// ================= Initial Servo Angles =================
int servoAngles[16] = {
  65, 60, 90, 20, 90, 20, 90, 140,
  90, 20, 90, 90, 90, 90, 90, 90
};

// ================= Servo Names =================
const char* servoNames[16] = {
  "Head", "Neck", "R_Shoulder", "R_ARM1", "R_ARM2", "R_Hand",
  "L_Shoulder", "L_ARM1", "L_ARM2", "L_Hand",
  "R_Leg", "R_Knee", "L_Leg", "L_Knee", "Servo14", "Servo15"
};

WebServer server(80);

// ================= Helper: Set Servo Angle =================
void setServoAngle(uint8_t ch, int angle) {
  angle = constrain(angle, 0, 180);
  servoAngles[ch] = angle;

  int pulseLen = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(ch, 0, pulseLen);
}

// ================= Smooth Movement =================
void moveServoSmooth(uint8_t ch, int targetAngle, int stepDelay) {
  int currentAngle = servoAngles[ch];

  if (targetAngle > currentAngle) {
    for (int pos = currentAngle; pos <= targetAngle; pos++) {
      setServoAngle(ch, pos);
      delay(stepDelay);
    }
  } else {
    for (int pos = currentAngle; pos >= targetAngle; pos--) {
      setServoAngle(ch, pos);
      delay(stepDelay);
    }
  }
}

// ================= Reset Position =================
void resetPosition() {

  moveServoSmooth(1, 90, 8);   // Neck
  moveServoSmooth(0, 90, 8);   // Head

  moveServoSmooth(2, 90, 10);  // R_Shoulder
  moveServoSmooth(3, 15, 10);  // R_ARM1
  moveServoSmooth(4, 90, 10);  // R_ARM2
  moveServoSmooth(5, 20, 10);  // R_Hand

  Serial.println("Reset Done!");
}

// ================= Salute Action =================
void performSalute() {
  Serial.println("Performing salute...");

  moveServoSmooth(1, 67, 8);   // Neck
  moveServoSmooth(0, 107, 8);  // Head

  moveServoSmooth(2, 90, 8);   // R_Shoulder
  moveServoSmooth(3, 113, 8);  // R_ARM1
  moveServoSmooth(4, 155, 8);  // R_ARM2
  moveServoSmooth(5, 139, 8);  // R_Hand

  Serial.println("Salute Done!");
}

// ================= Web Page =================
String htmlPage() {
  String page;
  page += "<!DOCTYPE html><html><head>";
  page += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  page += "<style>";
  page += "body{font-family:Arial;text-align:center;}";
  page += ".servoBox{border:1px solid #ccc;padding:10px;margin:10px;display:inline-block;}";
  page += "button{margin:2px;padding:5px 10px;}";
  page += "input[type=range]{width:200px;}";
  page += "</style></head><body>";

  page += "<h2>ESP32 PCA9685 Humanoid Controller</h2>";

  for (int i = 0; i < 16; i++) {
    page += "<div class='servoBox'><h3>";
    page += servoNames[i];
    page += " (" + String(i) + ")</h3>";

    page += "<input type='range' min='0' max='180' value='";
    page += servoAngles[i];
    page += "' id='slider" + String(i) + "'";
    page += " oninput='updateLabel(" + String(i) + ", this.value)'";
    page += " onchange='sendValue(" + String(i) + ", this.value)'>";

    page += "<br><button onclick='changeVal(" + String(i) + ", -1)'>-</button>";
    page += "<span id='label" + String(i) + "'>" + String(servoAngles[i]) + "</span>°";
    page += "<button onclick='changeVal(" + String(i) + ", 1)'>+</button>";
    page += "</div>";
  }

  page += "<br><br><button style='font-size:18px;background-color:orange;' onclick='recordAction()'>Record Action</button>";
  page += "<br><br><button style='font-size:18px;background-color:lightgreen;' onclick='saluteAction()'>Salute</button>";
  page += "<br><br><button style='font-size:18px;background-color:lightblue;' onclick='resetAction()'>Reset</button>";

  page += "<script>";
  page += "function updateLabel(ch,val){document.getElementById('label'+ch).innerText=val;}";
  page += "function sendValue(ch,val){fetch(`/set?ch=${ch}&val=${val}`);}";
  page += "function changeVal(ch,d){let s=document.getElementById('slider'+ch);";
  page += "let v=parseInt(s.value)+d; if(v<0)v=0;if(v>180)v=180;";
  page += "s.value=v;updateLabel(ch,v);sendValue(ch,v);}";
  page += "function recordAction(){fetch('/record').then(r=>r.text()).then(t=>alert(t));}";
  page += "function saluteAction(){fetch('/salute');}";
  page += "function resetAction(){fetch('/reset');}";
  page += "</script></body></html>";

  return page;
}

// ================= HTTP Handlers =================
void handleRoot() {
  server.send(200, "text/html", htmlPage());
}

void handleSet() {
  if (server.hasArg("ch") && server.hasArg("val")) {
    int ch = server.arg("ch").toInt();
    int val = server.arg("val").toInt();

    if (ch >= 0 && ch < 16) {
      setServoAngle(ch, val);
      server.send(200, "text/plain", "OK");
      return;
    }
  }
  server.send(400, "text/plain", "Bad Request");
}

void handleRecord() {
  Serial.println("----- Recorded Action -----");
  Serial.printf("%-4s %-12s %-10s\n", "No", "Name", "Angle");
  for (int i = 0; i < 16; i++) {
    Serial.printf("%-4d %-12s %-10d\n", i, servoNames[i], servoAngles[i]);
  }
  Serial.println("---------------------------");

  server.send(200, "text/plain", "Action recorded! Check Serial Monitor.");
}

void handleSalute() {
  performSalute();
  server.send(200, "text/plain", "Salute Performed");
}

void handleReset() {
  resetPosition();
  server.send(200, "text/plain", "Reset Done");
}

// ================= Setup =================
void setup() {
  Serial.begin(115200);
  Wire.begin();

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);

  for (int i = 0; i < 16; i++) {
    setServoAngle(i, servoAngles[i]);
  }

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/set", handleSet);
  server.on("/record", handleRecord);
  server.on("/salute", handleSalute);
  server.on("/reset", handleReset);

  server.begin();
  Serial.println("HTTP Server Started");
}

// ================= Loop =================
void loop() {
  server.handleClient();
}
