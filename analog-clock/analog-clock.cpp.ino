#include <scheduler.h>
#define LED_PIN 48
#define D3 6
#define D4 7
#define D5 8
#define D6 9
#define D7 10
#define D8 17
#define D9 18
#define D10 21

int led_status = 0;
void test_blinky(){
  led_status = 1 - led_status;
  digitalWrite(LED_PIN, led_status);
}


void displayOnClock(int i) {
  switch(i) {
    case 0:
    digitalWrite(D3, HIGH);digitalWrite(D4, HIGH);
    digitalWrite(D5, LOW);digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);digitalWrite(D8, LOW);
    digitalWrite(D9, LOW);digitalWrite(D10, LOW);
    break;
    case 1:
    digitalWrite(D3, LOW);digitalWrite(D4, HIGH);
    digitalWrite(D5, LOW);digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);digitalWrite(D8, LOW);
    digitalWrite(D9, LOW);digitalWrite(D10, LOW);
    break;
    case 2:
    digitalWrite(D3, HIGH);digitalWrite(D4, LOW);
    digitalWrite(D5, LOW);digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);digitalWrite(D8, LOW);
    digitalWrite(D9, LOW);digitalWrite(D10, LOW);
    break;
    case 3:
    digitalWrite(D3, LOW);digitalWrite(D4, LOW);
    digitalWrite(D5, HIGH);digitalWrite(D6, HIGH);
    digitalWrite(D7, LOW);digitalWrite(D8, LOW);
    digitalWrite(D9, LOW);digitalWrite(D10, LOW);
    break;
    case 4:
    digitalWrite(D3, LOW);digitalWrite(D4, LOW);
    digitalWrite(D5, LOW);digitalWrite(D6, HIGH);
    digitalWrite(D7, LOW);digitalWrite(D8, LOW);
    digitalWrite(D9, LOW);digitalWrite(D10, LOW);
    break;
    case 5:
    digitalWrite(D3, LOW);digitalWrite(D4, LOW);
    digitalWrite(D5, HIGH);digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);digitalWrite(D8, LOW);
    digitalWrite(D9, LOW);digitalWrite(D10, LOW);
    break;
    case 6:
    digitalWrite(D3, LOW);digitalWrite(D4, LOW);
    digitalWrite(D5, LOW);digitalWrite(D6, LOW);
    digitalWrite(D7, HIGH);digitalWrite(D8, HIGH);
    digitalWrite(D9, LOW);digitalWrite(D10, LOW);
    break;
    case 7:
    digitalWrite(D3, LOW);digitalWrite(D4, LOW);
    digitalWrite(D5, LOW);digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);digitalWrite(D8, HIGH);
    digitalWrite(D9, LOW);digitalWrite(D10, LOW);
    break;
    case 8:
    digitalWrite(D3, LOW);digitalWrite(D4, LOW);
    digitalWrite(D5, LOW);digitalWrite(D6, LOW);
    digitalWrite(D7, HIGH);digitalWrite(D8, LOW);
    digitalWrite(D9, LOW);digitalWrite(D10, LOW);
    break;
    case 9:
    digitalWrite(D3, LOW);digitalWrite(D4, LOW);
    digitalWrite(D5, LOW);digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);digitalWrite(D8, LOW);
    digitalWrite(D9, HIGH);digitalWrite(D10, HIGH);
    break;
    case 10:
    digitalWrite(D3, LOW);digitalWrite(D4, LOW);
    digitalWrite(D5, LOW);digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);digitalWrite(D8, LOW);
    digitalWrite(D9, LOW);digitalWrite(D10, HIGH);
    break;
    case 11:
    digitalWrite(D3, LOW);digitalWrite(D4, LOW);
    digitalWrite(D5, LOW);digitalWrite(D6, LOW);
    digitalWrite(D7, LOW);digitalWrite(D8, LOW);
    digitalWrite(D9, HIGH);digitalWrite(D10, LOW);
    break;
  }
}

int second = 0;

void task1(){
  displayOnClock(second);
  second++;
  if (second>11){
    second=0;
  }
}


void TIMER_ISR(void *pvParameters) {
  
  while(1) {
    SCH_Update();
    vTaskDelay(10);
  }
}
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D8, OUTPUT);
  pinMode(D9, OUTPUT);
  pinMode(D10, OUTPUT);

  digitalWrite(D3, LOW);digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);digitalWrite(D6, LOW);
  digitalWrite(D7, LOW);digitalWrite(D8, LOW);
  digitalWrite(D9, LOW);digitalWrite(D10, LOW);

  xTaskCreate(TIMER_ISR, "TIMER_ISR", 2048, NULL, 2, NULL);

  SCH_Init();
  SCH_Add_Task(test_blinky, 0, 100);

  SCH_Add_Task(task1, 0 , 100);
}

void loop() {
  SCH_Dispatch_Tasks();
}
