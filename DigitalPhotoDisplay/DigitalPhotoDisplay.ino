/*
 * TFT Image Slideshow
 *
 * This project uses and adapts functionality from Adafruit's
 * Adafruit_ImageReader library and its example sketches for
 * loading BMP images from an SD card and displaying them on
 * an Adafruit TFT display.
 *
 * Adafruit ImageReader:
 * https://github.com/adafruit/Adafruit_ImageReader
 *
 * Adafruit ImageReader documentation:
 * https://adafruit.github.io/Adafruit_ImageReader/
 *
 * Original library/example code is provided by Adafruit Industries
 * under the applicable open-source license. Project-specific code,
 * including the welcome screen, circle animation, image list,
 * slideshow logic, and hardware configuration, was modified for
 * this project.
 */
#include <SPI.h>
#include <Adafruit_GFX.h>         // Core graphics library
#include <Adafruit_HX8357.h>      // Hardware-specific library
#include <SdFat.h>                // SD card & FAT filesystem library
#include <Adafruit_ImageReader.h> // Image-reading functions

/* The TFT and SD card share the same SPI communication lines but have separate Chip Select pins.
The Chip Select pins are how the TFT knows if the message is meant for it or for the SD card*/

#define USE_SD_CARD
#define SD_CS    5                // SD card chip select pin
#define TFT_CS   9                // TFT chip select pin
#define TFT_DC   10               // Tells TFT whether info coming in is a comman or display data

SdFat                SD;          // Creates SD card object
Adafruit_ImageReader reader(SD);  // Image-reader object, pass in SD filesystem
Adafruit_HX8357        tft    = Adafruit_HX8357(TFT_CS, TFT_DC); // Creates tft object


//const char* imageFiles[] = {"/a.bmp", "/b.bmp", "/c.bmp", "/e.bmp", "/f.bmp", "/g.bmp","/h.bmp", "/i.bmp", "/j.bmp", "/k.bmp", 
 //"/q.bmp", "/r.bmp", "/s.bmp", "/t.bmp", "/u.bmp", "/v.bmp", "/w.bmp", "/x.bmp", "/y.bmp", "/z.bmp"};

const char* imageFiles[] = {"mama.bmp", "main.bmp", "shriya.bmp", "close.bmp"};

const int IMAGE_COUNT = sizeof(imageFiles) / sizeof(imageFiles[0]);
int count = 0;

void setup(void) {

  Serial.begin(9600);
  while (!Serial);
  tft.begin();          // Initialize screen

  Serial.print(F("Initializing filesystem..."));
  Serial.println(F("Initializing SD card..."));

  if (!SD.begin(SD_CS)) {
      Serial.println(F("SD card initialization failed."));
      for (;;) {
      }
  }

  Serial.println(F("SD card initialized."));
  Serial.println(F("OK!"));

  //Display purple welcome message on black background
  tft.fillScreen(HX8357_BLACK);
  tft.setCursor(40, 100);
  tft.setTextSize(5);
  tft.setTextColor(0xF231);
  tft.println("Welcome!");
  delay(2000); // Pause 2 seconds before moving on to loop()

  //Display pretty purple circles filling the screen (intro animation)
  tft.fillScreen(HX8357_BLACK);
  uint16_t radius = 10;
  uint16_t color = 0xF231;
  unsigned long start;
  int           x, y, r2 = radius * 2,
                w = tft.width()  + radius,
                h = tft.height() + radius;

  start = micros();
  for(y=0; y<h; y+=r2) {
    for(x=0; x<w; x+=r2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
 delay(500);

}

void loop() {
  
  char* current = imageFiles[count];

  ImageReturnCode stat = stat = reader.drawBMP(current, tft, 0, 0);

  if (stat != IMAGE_SUCCESS) {
    Serial.print(F("Error displaying "));
    Serial.println(current);
    reader.printStatus(stat);
  }

  count++;

  if(count >= IMAGE_COUNT){
    count = 0;
  }

  delay(500); 
}

