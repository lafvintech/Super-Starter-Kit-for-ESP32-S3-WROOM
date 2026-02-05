#include "sd_read_write.h"
#include "SD_MMC.h"

#define SD_MMC_CMD 38 //Please do not modify it.
#define SD_MMC_CLK 39 //Please do not modify it. 
#define SD_MMC_D0  40 //Please do not modify it.

void setup(){
    Serial.begin(115200);  // Initialize serial communication
    SD_MMC.setPins(SD_MMC_CLK, SD_MMC_CMD, SD_MMC_D0);  // Set SD card pins
    if (!SD_MMC.begin("/sdcard", true, true, SDMMC_FREQ_DEFAULT, 5)) {  // Mount SD card
      Serial.println("Card Mount Failed");
      return;
    }
    uint8_t cardType = SD_MMC.cardType();  // Get SD card type
    if(cardType == CARD_NONE){
        Serial.println("No SD_MMC card attached");
        return;
    }

    // Print SD card type
    Serial.print("SD_MMC Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    // Print SD card size
    uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
    Serial.printf("SD_MMC Card Size: %lluMB\n", cardSize);

    listDir(SD_MMC, "/", 0);  // List root directory contents

    createDir(SD_MMC, "/mydir");  // Create a directory
    listDir(SD_MMC, "/", 0);  // List root directory again

    removeDir(SD_MMC, "/mydir");  // Remove the created directory
    listDir(SD_MMC, "/", 2);  // List root directory with depth 2

    writeFile(SD_MMC, "/hello.txt", "Hello ");  // Write to a file
    appendFile(SD_MMC, "/hello.txt", "World!\n");  // Append to the file
    readFile(SD_MMC, "/hello.txt");  // Read the file

    deleteFile(SD_MMC, "/foo.txt");  // Delete a file (if it exists)
    renameFile(SD_MMC, "/hello.txt", "/foo.txt");  // Rename a file
    readFile(SD_MMC, "/foo.txt");  // Read the renamed file

    testFileIO(SD_MMC, "/test.txt");  // Perform I/O test on a file
    
    // Print total and used space on the SD card
    Serial.printf("Total space: %lluMB\r\n", SD_MMC.totalBytes() / (1024 * 1024));
    Serial.printf("Used space: %lluMB\r\n", SD_MMC.usedBytes() / (1024 * 1024));
}

void loop(){
  delay(10000);  // Wait for 10 seconds
}