#include <VirtualWire.h>

const int led_pin = 13;  //the led to light up, to indicate we are recieving a message
const int receive_pin = 11;
const int transmit_en_pin = 3;

void debugMessage(String message, int value) {
  message += value;
  Serial.println(message);
}


void setup()
{
  
  debugMessage("Setting up Reciever", 0);
  
    delay(1000);
    Serial.begin(9600);	// Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec

    vw_rx_start();       // Start the receiver PLL running

    pinMode(led_pin, OUTPUT);
}

void loop()
{

    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    String message;
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
        //example 
        // 1 6B 
        // 1 = the plant_number
        // 6B = moisture_level
         
        digitalWrite(led_pin, HIGH); // Flash a light to show received good message
	// Message with a good checksum received, dump it.

        int plant_number = buf[0];
        int moisture_level = buf[1];
        
        debugMessage("Plant number ", plant_number);
        debugMessage("Moisture Level ", moisture_level);

        digitalWrite(led_pin, LOW);
    }
}
