
/*
  Задания - это этапы выполнения лабораторной работы.
  Незакоментированный код относится к выполнению задачи первого кейса, 
  заключающегося в реализации электронного кодового замка
  с помощью электромагнитного реле и четырекнопочной клавиатуры
*/

#include "mbed.h"

/* Первое задание
DigitalIn mybutton(USER_BUTTON);
DigitalOut myled(LED1);
*/

/* Второе задание
PwmOut led(LED1);
int brightness = 0;
*/

/* Третье задание 
AnalogIn my_adc(PA_7); //D11 on board
DigitalOut led(LED1);
*/

/* Задача кейса */

DigitalIn buttonS1(PA_0);
DigitalIn buttonS2(PA_1);
DigitalIn buttonS3(PA_4);
DigitalIn buttonS4(PB_0); 

DigitalOut ReleyControl(PC_1);
DigitalOut led(LED1);

#define VALID_KEY 0x36 // Валидный ключ
#define KEY_LENGTH 0x04 // Длина валидного ключа

#define BUTTON1_CODE 0 // Коды кнопок
#define BUTTON2_CODE 1
#define BUTTON3_CODE 2
#define BUTTON4_CODE 3

uint8_t currentKeylength = 0; // Счетчик нажатий
uint8_t currentInput = 0; // Буфер последовтельности нажатий

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
/* Третье задание 
  printf("\nSTM32 ADC example\n");

  while(1) {
      printf("ADC read = %i\n\r", (my_adc.read()*100));
      led = !led;
      wait_us(10000);
  }


*/

/* Задача кейса */
  ReleyControl = 0; // Дверь заперта
  led = 1; // Лампочка горит, когда дверь заперта

  buttonS1.mode(PullUp);
  buttonS2.mode(PullUp);
  buttonS3.mode(PullUp);
  buttonS4.mode(PullUp);


  while(1){
    // Опрашиваем состояние кнопок
    //==============================
    if (!buttonS1) {
      currentKeylength++; // Инкрементируем счетчик нажатий
      currentInput <<= 2;  // Сдвигаем последовательность кодов нажатий
      currentInput |= BUTTON1_CODE; // Записываем код очередного нажатия
    }
    if (!buttonS2) {
      currentKeylength++;
      currentInput <<= 2;
      currentInput |= BUTTON2_CODE;  
    }
    if (!buttonS3) {
      currentKeylength++;
      currentInput <<= 2;
      currentInput |= BUTTON3_CODE; 
    }
    if (!buttonS4) {
      currentKeylength++; 
      currentInput <<= 2;
      currentInput |= BUTTON4_CODE; 
    }
    //==============================
    printf("Current input: %X\n", currentInput);
    wait_us(500000);
    //currentKeylength = 0;
    // Контроллируем количество нажатий на кнопки и открываем дверь при валидном ключе
    
    if (currentKeylength >= 4) {
      currentKeylength = 0; // Обнуляем счетчик нажатий
    
      if (currentInput == VALID_KEY) { // Сравниваем набранную в буфер последовательность нажатий с ключом
        ReleyControl = !ReleyControl; // Открываем дверь
        // Мигаем лампочкой в течение ~10 секунд
        for (uint8_t t = 0; t < 20; t++){ 
          led = !led; 
          wait_us(500000);
        } 
      }
      ReleyControl = 0; // Закрываем дверь
      led = 1; // Включаем постоянное свечение лампочки
      currentInput = 0; // Очищаем буфер
    }
  }
}
