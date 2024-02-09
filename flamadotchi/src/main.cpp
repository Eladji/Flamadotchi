#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <image.h>
#include <pass.h>
#define BUTTON_PIN 17 // GIOP17 pin connected to button
#define BUTTON_PIN2 18 // GIOP18 pin connected to button
#define Led_Pin 13 // GIO13 is the led pin
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
bool emochang = true;
int spriteX = 105;
int spriteY = 38;
int sensx = 1;
int sensy = 1;
int i = 0;
const int frames = 7; 
// put function declarations here:
int myFunction(int, int);

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PIN2, INPUT_PULLUP);
  pinMode(Led_Pin, OUTPUT);
 int buttonState = digitalRead(BUTTON_PIN);
  int buttonState2 = digitalRead(BUTTON_PIN2);
  Serial.begin(115200);
  srand( time( NULL ) );

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
       xTaskCreatePinnedToCore(
    secondCoreFunction, /* Function to implement the task */
    "secondCoreTask",   /* Name of the task */
    10000,              /* Stack size in words */
    NULL,               /* Task input parameter */
    0,                  /* Priority of the task */
    NULL,               /* Task handle. */
    1);  
  }
display.clearDisplay();
display.setTextSize(1);           
display.setTextColor(SSD1306_WHITE);      
display.setCursor(0,0); 
srand(time(0)); // Seed the random number generator
display.println("Connecting to WiFi...");
display.display();
WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  Serial.print("CONNECTED to SSID: ");
  Serial.println(ssid);

  display.print("Connected to ");
  display.println(ssid);
  display.display();
  delay(5000);
}

void idle(){
  for (int frame = 0; frame < frames; ++frame) {
        display.clearDisplay();
        display.drawBitmap(0, 0, flaflame[frame], 20, 24, 1);
        display.display();
        delay(50); // Adjust the delay as needed for the animation speed
    }
      for (int frame = frames - 1; frame >= 0; --frame) {
        display.clearDisplay();
        display.drawBitmap(0, 0, flaflame[frame], 20, 24, 1);
        display.display();
        delay(50); // Adjust the delay as needed for the animation speed
    }
}
// emotion fonction
void happy(){
display.drawBitmap(4, 14, eyes, 11, 3, 1);
}
void sad(){
display.drawBitmap(4, 13, eyes, 11, 3, 1);  
}
void angry(){
display.drawBitmap(4, 15, eyes, 11, 3, 1);  
}
void neutral(){
display.drawBitmap(4, 16, eyes, 11, 3, 1);  
}       

// Function to randomly execute one of the four functions
void executeRandomFunction() {
    // Seed the random number generator
    

    // Generate a random number between 1 and 4
    int randomNum = rand() % 4 + 1;

    // Call the corresponding function based on the random number
    switch (randomNum) {
        case 1:
            neutral();
            break;
        case 2:
            angry();
            break;
        case 3:
            sad();
            break;
        case 4:
            happy();
            break;
        default:
            // Handle unexpected case
            Serial.println("Error: Invalid random number");
            break;
    }
}

void moveSprite() {
  
  if (spriteX == 105){
      sensx = -1;
    }
    else if(spriteX == 0){
      sensx = 1;
    }
      if (spriteY == 38){
      sensy = -1;
    }
    else if(spriteY == 0){
      sensy = 1;
    }
  
    //if spritey = 38
    spriteX = spriteX + 1 * sensx;
    spriteY = spriteY + 1 * sensy;
  
  return;

}

TaskHandle_t secondCoreTask;
// Function to be executed on the second core
void secondCoreFunction(void *parameter) {
  while (emochang == true) {
    // Call the function on the first core
    executeRandomFunction();

    // Delay for a random amount of time
    setrandomtimer(parameter);
  }
}

// Function to set a random delay and run on the second core for multitasking (max : 60s | min : 20)
void setrandomtimer(void *parameter){
  int randomNum = rand() % 41 + 20;
  delay(randomNum * 1000);

}

void loop() {


         for (int frame = 0; frame < frames; ++frame) {
        display.clearDisplay();
        //executeRandomFunction();
        moveSprite();
        display.drawBitmap(spriteX, spriteY, flaflame[frame], 20, 24, 1);
       
        display.display();
        delay(50); // Adjust the delay as needed for the animation speed
    }
      for (int frame = frames - 1; frame >= 0; --frame) {
        display.clearDisplay();
        moveSprite();
      
        display.drawBitmap(spriteX, spriteY, flaflame[frame], 20, 24, 1);
        display.display();
        delay(50); // Adjust the delay as needed for the animation speed
    }

}

