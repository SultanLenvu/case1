#include "mbed.h"

// DigitalIn mybutton(USER_BUTTON);
// DigitalOut myled(LED1);

BufferedSerial pc(USBTX, USBRX); // tx, rx
PwmOut led(LED1);
float brightness = 0.0;

int main()
{
  printf("Control of LED dimmer by host terminal\n\r");
  printf("Press 'u' = brighter, 'd' = dimmer\n\r");

  // if (mybutton == 0) { // Button is pressed

  //     myled = !myled; // Toggle the LED state
  //     wait_ms(200); // 200 ms
  // }

  while(1) {
    char c = getchar();
    wait_us(10);

            if((c == 'u') && (brightness < 0.1)) {
        brightness += 0.001;
        led = brightness;
    }

    if((c == 'd') && (brightness > 0.0)) {
        brightness -= 0.001;
        led = brightness;
    }
    printf("%c %f \n \r",c, brightness);
  }
}
