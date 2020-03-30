#include <FreeRTOS.h>
#include <task.h>

#define STK_SZ  128

StackType_t stk1[STK_SZ], stk2[STK_SZ], stki[STK_SZ];
StaticTask_t tcb1, tcb2, tcbi;

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer   = &tcbi;
  *ppxIdleTaskStackBuffer = stki;
  *pulIdleTaskStackSize   = STK_SZ;
}

void blinky(void* arg)
{
  unsigned long i;
  unsigned char mask;

  mask = 1<<(*((unsigned char*)arg));

  DDRD |= mask;
  while(1)
  {
    PORTD |= mask;
    for(i=0; i<100000; i++);
    PORTD &= ~mask;
    for(i=0; i<100000; i++);
  }

}

void vApplicationIdleHook()
{

}

void main()
{
  unsigned char p1 = 0, p2 = 1;
  xTaskCreateStatic(blinky, "", STK_SZ, (void*)&p1, 1, stk1, &tcb1);
  xTaskCreateStatic(blinky, "", STK_SZ, (void*)&p2, 1, stk2, &tcb2);

  vTaskStartScheduler();
}
