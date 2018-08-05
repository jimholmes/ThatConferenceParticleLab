// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_SSD1306.h>
#include <Adafruit_Si7021.h>

int yellowLED = A0;
int blueLED = A1;
int greenLED = A2;
int redLED = A3;

bool isBlueOn = false;
bool isGreenOn = false;

int currentTemp;
int currentHumidity;

Adafruit_SSD1306 display(RESET);
Adafruit_Si7021 sensor = Adafruit_Si7021();


void toggle(bool isOn, int led) {
  if (isOn)
  {
      digitalWrite(led, LOW);
  }
  else
  {
      digitalWrite(led, HIGH);
  }
}


void toggleGreen(const char *event, const char *data)
{
  toggle(isGreenOn, greenLED);
  isGreenOn = !isGreenOn;
}

int toggleBlue(String command)
{
  toggle(isBlueOn, blueLED);
  isBlueOn = !isBlueOn;

  return 1;
}

void initialize_display() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  display.clearDisplay();
  display.setTextWrap(true);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println("");
  display.println("Jim");
  display.println("Holmes");
  display.setTextSize(1);
  display.println("");
  display.println("@aJimHolmes");
  display.display();

}

void initialize_pins() {
  pinMode(yellowLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
}

void initialize_cloud_calls() {
  Particle.function("toggleBlue", toggleBlue);
  Particle.variable("greenOn", isGreenOn);
  Particle.subscribe("toggleGreen", toggleGreen, MY_DEVICES);
}

void initialize_sensor() {
  sensor.begin();
  Particle.variable("temp", currentTemp);
  Particle.variable("humidity", currentHumidity);
  currentTemp = round((sensor.readTemperature() * 1.8 + 32.00) * 10) / 10;
  currentHumidity = round(sensor.readHumidity()*10)/10;

}

void setup() {
  initialize_pins();
  initialize_cloud_calls();
  initialize_display();
  initialize_sensor();
}

void loop() {

}
