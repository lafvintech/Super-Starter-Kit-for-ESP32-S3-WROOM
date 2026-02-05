import os
import sys
import time

# 指定COM15端口，擦除ESP32-S3芯片上的Flash存储器
os.system("python esptool/esptool.py --port COM15 --chip esp32s3 erase_flash")

# 指定COM15端口，使用2000000波特率将固件烧录到ESP32-S3芯片上
os.system("python esptool/esptool.py --port COM15 --chip esp32s3 --baud 2000000 write_flash -z 0 GENERIC_S3-20220618-v1.19.1.bin")