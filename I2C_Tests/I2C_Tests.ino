#include <Wire.h>
#include <Servo.h>

#define TESTING

#define I2C_ADDR 0x52

#define MAIN_CTRL 0x00
#define PWR_ON 0b00000110

#define LS_MEAS_RATE 0x04
#define LS_RES_MSR 0b01000000

#define CDATA_ADDR 0x0A

// i found some sensor values online, thanks to SANELSS
#define LED_RED 7540.0f
#define LED_GREEN 14470.0f
#define LED_BLUE 7270.0f
 
#define BAL_RED (LED_GREEN/LED_RED)
#define BAL_GREEN (LED_GREEN/LED_GREEN) 
#define BAL_BLUE (LED_GREEN/LED_BLUE)

#define SERVO_PIN 11
#define IND_LED_PIN 12
#define RESET 10

// record values of ball colors here...
// wood
#define R_W_MAX 175
#define R_W_MIN 124
#define G_W_MAX 247
#define G_W_MIN 200
#define B_W_MAX 206
#define B_W_MIN 188
#define IR_W_MAX 188
#define IR_W_MIN 204

// plastic
#define R_PL_MAX 183
#define R_PL_MIN 163
#define G_PL_MAX 110
#define G_PL_MIN 92
#define B_PL_MAX 161
#define B_PL_MIN 139
#define IR_PL_MAX 161
#define IR_PL_MIN 139

// note the most difference is between green


uint8_t buf[9];

uint16_t r = 0, g = 0, b = 0, ir = 0;

int count = 0;

Servo servo;

void setup() {
  pinMode(IND_LED_PIN, OUTPUT);
  digitalWrite(IND_LED_PIN, HIGH);
  Wire.begin();
  
  #ifdef TESTING
  Serial.begin(115200);
  #endif

  I2CWrite(MAIN_CTRL, PWR_ON);
  I2CWrite(LS_MEAS_RATE, LS_RES_MSR);
  digitalWrite(IND_LED_PIN, LOW);
  servo.attach(SERVO_PIN);
  servo.write(90); // set servo to middle
}

void loop() {
  digitalWrite(IND_LED_PIN, HIGH);
  
  I2CRead(CDATA_ADDR, buf, 12);

  // value assignment is based on the struture of the byte at 
  ir = (buf[1] << 8 | buf[0]);
  g = (buf[4] << 8 | buf[3]);  
  b = (buf[7] << 8 | buf[6]);
  r = (buf[10] << 8 | buf[9]);

  // balance
  r *= BAL_RED;
  g *= BAL_GREEN;
  b *= BAL_BLUE;

  #ifdef TESTING
  //PrintVals(r, g, b, ir);
  #endif
  
  // check values
  // todo: counter
  bool loopOk = count % 8 == 0;

  if (loopOk)
  {
    Serial.print("IR: "); 
    Serial.print(ir);
    Serial.print(" ");
  }
  
  if (ir > 50 && loopOk) // condition for plastic here
  { 
    Serial.println("fired plastic"); 
    servo.write(45);
  }
  else if (!(ir < 10) && loopOk)// condition for wood here*/
  { 
    Serial.println("fired wood"); 
    servo.write(180 - 45); 
  }
  else if (loopOk)
  {
    servo.write(90); 
    Serial.println("fired none"); 
  }

  count++;
  delay(25);
}

void I2CRead(uint8_t reg, uint8_t *val, uint16_t len)
{
  pinMode(IND_LED_PIN, HIGH);
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(I2C_ADDR, len);
  for (uint8_t i = 0; i < len; i++)
  {val[i] = Wire.read();}
  pinMode(IND_LED_PIN, LOW);
}

void I2CWrite(uint8_t raddr, uint8_t payload)
{
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(raddr);
  Wire.write(payload);
  Wire.endTransmission();
}

void PrintVals(uint16_t r, uint16_t g, uint16_t b, uint16_t ir)
{
  PRI("Red: ");
  PRI(r);
  PRI(" Green: ");
  PRI(g);
  PRI(" Blue: ");
  PRI(b);
  PRI(" IR: ");
  PRI(b);
  PR("");
}

void PR(String p) {Serial.println(p);}
void PR(uint8_t p) {Serial.println(p);}
void PRI(String p) {Serial.print(p);}
void PRI(uint8_t p) {Serial.print(p);}
