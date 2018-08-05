// This #include statement was automatically added by the Particle IDE.
#include <Adafruit_SSD1306.h>

int yellowLED = A0;
int blueLED = A1;
int greenLED = A2;
int redLED = A3;

bool isBlueOn = false;
bool isGreenOn = false;

Adafruit_SSD1306 display(RESET);



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

void setup() {
  pinMode(yellowLED, OUTPUT); // Yellow
  pinMode(blueLED, OUTPUT); // Blue
  pinMode(greenLED, OUTPUT); // Green
  pinMode(redLED, OUTPUT); // Red

  Particle.function("toggleBlue", toggleBlue);
  Particle.variable("greenOn", isGreenOn);
  Particle.subscribe("toggleGreen", toggleGreen, MY_DEVICES);

  initialize_display;
}

void loop() {
    
}
