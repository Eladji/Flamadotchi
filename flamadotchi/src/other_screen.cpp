#include <WiFi.h>
#include <HTTPClient.h>

HTTPClient http;
String previousNumbers;
String concatenatedNumbers;

void rule34(Adafruit_SSD1306 display, String previousNumbers, String concatenatedNumbers, String rule34I){

  
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Getting data...");HTTPClient

    http.begin("https://rule34.xxx");
    int httpCode = http.GET();

    if (httpCode > 0)
    {
      String html = http.getString();

      int startIndex = html.indexOf("<img src=\"./counter/");
      int endIndex = html.indexOf("\">", startIndex);
      String counterTags = html.substring(startIndex, endIndex);

      concatenatedNumbers = ""; // Reset the string before extracting new numbers

      int index = 0;
      while ((index = counterTags.indexOf("alt=\"", index)) != -1)
      {
        int numberStart = index + 5;
        int numberEnd = counterTags.indexOf("\"", numberStart);
        String number = counterTags.substring(numberStart, numberEnd);
        concatenatedNumbers += number;
        index = numberEnd;
      }
      display.clearDisplay();
      display.drawBitmap(25, 0, rule34I, 63, 35, WHITE);
      
      display.setTextSize(1);
      printCenter("Numbers: " + concatenatedNumbers, 0, 32);
      display.display();

      if (concatenatedNumbers != previousNumbers)
      {
        display.clearDisplay();
        display.drawBitmap(25, 0, rule34I, 63, 35, WHITE);
        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        
        printCenter("Numbers: " + concatenatedNumbers, 0, 32);
        display.display();

        previousNumbers = concatenatedNumbers;
      }
    }
    http.end();
    delay(5000); // Wait for 5 seconds before making the next request
}
}