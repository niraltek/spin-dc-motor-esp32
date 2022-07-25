#define Sound_sensor 34
#define motorPin1 26
#define motorPin2 27

const int sampleWindow = 50; //sample window width in ms(50mS=20Hz)
const int dbMax = 70;
unsigned int volume;

void setup()
{
  pinMode(Sound_sensor, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  unsigned long startMillis = millis(); //start of sample window
  int peakToPeak = 0; //peak-to-peak level

  unsigned int signalMax = 0; //minimum value
  unsigned int signalMin = 4096; //maximum value

  while (millis() - startMillis < sampleWindow) //collect data for 50ms
  {
    volume = analogRead(Sound_sensor); //get reading from microphone

    if (volume < signalMin) {
      if (volume > signalMax)
      {
        signalMax = volume;
      }

    }

  }

  peakToPeak = signalMax;
  int db = (peakToPeak / 10);
  Serial.print("Db = ");
  Serial.println(db);

  if (db > dbMax) {
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
  }
  else {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
  }
}
