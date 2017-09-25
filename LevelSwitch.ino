// Level Switch for Waterpump
// Niveauschalter für Wasserpumpe
// MWR 20.12.2016

//LED 2-color, common Anode, Low=on
//ATMEGA328 3,3V

#define LED_RED       9
#define LED_ANODE     8
#define LED_GREEN     7

#define SENSOR_FEED   A0
#define SENSOR_EMPTY  A1  //Bucket empty
#define SENSOR_FULL   A2  //Bucket full

#define KEY1on    2
#define KEY1off   3


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_ANODE, OUTPUT);
  digitalWrite(LED_ANODE, HIGH);

  pinMode(KEY1on, OUTPUT);
  digitalWrite(KEY1on, HIGH);
  pinMode(KEY1off, OUTPUT);
  digitalWrite(KEY1off, HIGH);

  //pinMode(SENSOR_FULL, INPUT);
  //pinMode(SENSOR_EMPTY, INPUT);
  pinMode(SENSOR_FEED, OUTPUT);
  digitalWrite(SENSOR_FEED, LOW);

  //LED's off
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(115200);

}

void loop() {
  /*
    digitalWrite(LED_BUILTIN, HIGH);
  */
  byte pump;
  bool sSE, sSF;
  sSE=statusSE();
  sSF=statusSF();

  if ( sSF ) {
    pump = 1;
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
  }
  else if ( !sSE ) {
    pump = 0;
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
  }

  pumping(pump);

  delay(100);
}

void pumping( byte pump) {
  static byte pump_old = -1;

  if (pump>0 && (pump != pump_old)) {
    // Pumpe einschalten
    //pinMode(KEY1on, OUTPUT);
    digitalWrite(KEY1on, LOW);
    delay(1000);
    digitalWrite(KEY1on, HIGH);
    //pinMode(KEY1on, INPUT);

  } else if (pump<=0 && (pump != pump_old)) {
    // Pumpe ausschalten
    //pinMode(KEY1off, OUTPUT);
    digitalWrite(KEY1off, LOW);
    delay(1000);
    digitalWrite(KEY1off, HIGH);
    //pinMode(KEY1off, INPUT);
  }

  pump_old = pump;
}

bool statusSF() {
  bool _status;
  digitalWrite(SENSOR_FEED, HIGH);

  if (analogRead(SENSOR_FULL) >= 200) _status = true;
  else _status = false;

  digitalWrite(SENSOR_FEED, LOW);
  return _status;
}

bool statusSE() {
  bool _status;
  digitalWrite(SENSOR_FEED, HIGH);

  if (analogRead(SENSOR_EMPTY) >= 200) _status = true;
  else _status = false;

  digitalWrite(SENSOR_FEED, LOW);
  return _status;
}




