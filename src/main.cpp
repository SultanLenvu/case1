#include "mbed.h"

/* Первое задание
DigitalIn mybutton(USER_BUTTON);
DigitalOut myled(LED1);
*/

/* Второе задание
PwmOut led(LED1);
int brightness = 0;
*/

/* Третье задание */
AnalogIn my_adc(PA_7); //D11 on board
DigitalOut led(LED1);

int main(){
/* Первое задание
  if (mybutton == 0) { // Button is pressed

      myled = !myled; // Toggle the LED state
      wait_ms(200); // 200 ms
  }
*/

/* Первое задание
  while(1) {
    char c = getchar();
    wait_us(10);

    if((c == 'u') && (brightness < 1000)) {
        brightness += 1;
        led = (float)brightness/10000;
    }

    if((c == 'd') && (brightness > 0)) {
        brightness -= 1;
        led = (float)brightness/10000;
    }
    printf("%c %i \n \r",c, brightness);
  }
*/
/* Третье задание */
  printf("\nSTM32 ADC example\n");

  while(1) {
      printf("ADC read = %i\n\r", (my_adc.read()*100));
      led = !led;
      wait_us(10000);
  }
}
