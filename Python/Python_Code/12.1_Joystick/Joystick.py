from machine import ADC,Pin
import time

xVal=ADC(Pin(14))
yVal=ADC(Pin(13))

xVal.atten(ADC.ATTN_11DB)
yVal.atten(ADC.ATTN_11DB)
xVal.width(ADC.WIDTH_12BIT)
yVal.width(ADC.WIDTH_12BIT)

while True:
  print("X,Y:",xVal.read(),",",yVal.read())
  time.sleep(1)