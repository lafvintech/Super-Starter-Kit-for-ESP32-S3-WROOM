#include <Arduino.h>
#include <WiFi.h>
#include "FS.h"
#include "SD_MMC.h"
#include "AudioFileSourceSD_MMC.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2SNoDAC.h"

#define SD_MMC_CMD 38 //Please do not modify it.
#define SD_MMC_CLK 39 //Please do not modify it. 
#define SD_MMC_D0  40 //Please do not modify it.

AudioGeneratorMP3 *mp3;
AudioFileSourceID3 *id3;
AudioOutputI2SNoDAC *out;

AudioFileSourceSD_MMC *file = NULL;

// Called when a metadata event occurs (i.e. an ID3 tag, an ICY block, etc.
void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string)
{
  (void)cbData;
  Serial.printf("ID3 callback for: %s = '", type);

  if (isUnicode) {
    string += 2;
  }
  
  while (*string) {
    char a = *(string++);
    if (isUnicode) {
      string++;
    }
    Serial.printf("%c", a);
  }
  Serial.printf("'\n");
  Serial.flush();
}

void setup()
{
  WiFi.mode(WIFI_OFF); 
  Serial.begin(115200);
  delay(1000);
  SD_MMC.setPins(SD_MMC_CLK, SD_MMC_CMD, SD_MMC_D0);
  if (!SD_MMC.begin("/sdcard", true, true, SDMMC_FREQ_DEFAULT, 5)) {
      Serial.println("Card Mount Failed");
      return;
  }
  Serial.printf("Sample MP3 playback begins...\n");

  audioLogger = &Serial;
  file = new AudioFileSourceSD_MMC("/music/Good Time.mp3");
  id3 = new AudioFileSourceID3(file);
  id3->RegisterMetadataCB(MDCallback, (void*)"ID3TAG");
  //out = new AudioOutputI2S();
  out = new AudioOutputI2SNoDAC();
  out->SetPinout(12,13,14);//Set the audio output pin, Only 14 were used
  out->SetGain(3.5);//Setting the Volume
  mp3 = new AudioGeneratorMP3();
  mp3->begin(id3, out);
}

void loop()
{
  if (mp3->isRunning()) {
    if (!mp3->loop()) mp3->stop();
  } else {
    Serial.printf("MP3 done\n");
    delay(1000);
  }
}
