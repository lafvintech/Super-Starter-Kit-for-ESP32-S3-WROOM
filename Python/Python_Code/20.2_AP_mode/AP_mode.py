import network
import time

def setup_secure_ap():
    ssid = "Your_AP"
    password = "12345678"  # Password must be at least 8 characters
    
    ap = network.WLAN(network.AP_IF)
    ap.active(False)  # First, turn off the AP to ensure clearing any previous settings
    time.sleep(1)
    ap.active(True)
    
    # Configure AP with WPA2 encryption
    ap.config(essid=ssid, password=password, authmode=network.AUTH_WPA2_PSK)
    
    print("Setting up encrypted AP...")
    
    # Wait for AP activation
    for _ in range(10):  # Wait for up to 10 seconds
        if ap.active():
            print("AP setup successful")
            print("SSID:", ssid)
            print("Password:", password)
            print("IP address:", ap.ifconfig()[0])
            return True
        time.sleep(1)
    
    print("AP setup failed")
    return False

try:
    if setup_secure_ap():
        print("AP is up and running. You should now see an encrypted Wi-Fi network.")
    else:
        print("Unable to set up AP. Please check your hardware and firmware.")
except Exception as e:
    print("An error occurred:", str(e))

print("Program ended")