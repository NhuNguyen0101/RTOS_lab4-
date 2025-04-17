#include <scheduler.h>
#define LED_PIN 48
#define D3 6
#define D4 7
#define D5 8
#define D6 9

int led_status = 0;
void test_blinky(){
  led_status = 1 - led_status;
  digitalWrite(LED_PIN, led_status);
}

int i=9;
void task1(){
  if(i>=5 && i<10){
    RedLight();
    if (i>=5 && i<7){
      YellowLight2();
      }
    if (i>=7 && i<10){
      GreenLight2();
    }
  }
  if(i>=2 && i<5){
    GreenLight();
    
    RedLight2();
  }
  if(i>=0 && i<2){
    YellowLight();
    
    RedLight2();
  }
  i=i-1;
  if(i<0){
    i=9;
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

  offLight();
  xTaskCreate(TIMER_ISR, "TIMER_ISR", 2048, NULL, 2, NULL);

  SCH_Init();
  SCH_Add_Task(test_blinky, 0, 100);

  SCH_Add_Task(task1, 0 , 100);
}

void RedLight(){
  digitalWrite(D3, HIGH);digitalWrite(D4, HIGH);
}
void YellowLight(){
  digitalWrite(D3, LOW);digitalWrite(D4, HIGH);
}
void GreenLight(){
  digitalWrite(D3, HIGH);digitalWrite(D4, LOW);
}
void offLight(){
  digitalWrite(D3, LOW);digitalWrite(D4, LOW);
  digitalWrite(D5, LOW);digitalWrite(D6, LOW);
}

void RedLight2(){
  digitalWrite(D5, HIGH);digitalWrite(D6, HIGH);
}
void YellowLight2(){
  digitalWrite(D5, LOW);digitalWrite(D6, HIGH);
}
void GreenLight2(){
  digitalWrite(D5, HIGH);digitalWrite(D6, LOW);
}


void loop() {
  SCH_Dispatch_Tasks();
}
