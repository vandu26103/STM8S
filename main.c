#include "iostm8s103f3.h"
#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include <intrinsics.h>


volatile uint32_t SysTick = 0;

void Clock_Cfg(int MODE){
 /* CLK_SWR &= ~(0xFF);
  CLK_SWR |= 0xE1;
  
  CLK_CKDIVR &= ~(0x3<<3);
  CLK_CKDIVR |= 0x0<<3;
  CLK_CKDIVR &= ~0x7;
  CLK_CKDIVR |= 0x0;

*/
  CLK_SWR &= ~(0xFF);
  CLK_SWR |= MODE;
  
  CLK_CKDIVR &= ~(0x3<<3);
  CLK_CKDIVR |= 0x0<<3;
  CLK_CKDIVR &= ~0x7;
  CLK_CKDIVR |= 0x0;
}
void GPIO_Cfg(){
  PB_DDR |= (1 << 5); 
  PB_CR1 |= (1<<5);
  PB_CR2 &= ~(1<<5);
  
  PD_DDR |=  (1 << 3);   // Output
  PD_CR1 |=  (1 << 3);   // Push-pull
  PD_CR2 |=  (1 << 3);   // Fast mode (r?t quan tr?ng cho PWM)
}

void timer4_init(){
  TIM4_PSCR = 7; //prescaler
  TIM4_ARR = 124; //auto reload
  TIM4_IER = 1; // enable interrupt
  TIM4_CNTR = 0; //counter
  TIM4_EGR  = 1;
  TIM4_SR =0;
  TIM4_CR1 |= (1<<0);
}
 //timer 4 delay - 8bit
void delay4_ms(uint32_t time){
  uint32_t Tick;
  while(time>0){
    Tick = SysTick;
    time--;
    while(Tick == SysTick);
    
  }
}
#pragma vector = TIM4_OVR_UIF_vector
__interrupt void TIM4_UPD_OVFFF_IRQHandlerrrrrr(){
    SysTick++;   
    TIM4_SR &= (unsigned char)(~0x01);
}

void timer2_init(){
   
    TIM2_CR1 = 0;

    TIM2_PSCR = 4;        // prescaler = 16
    TIM2_ARRH = 0x03;
    TIM2_ARRL = 0xE7;     // 1000
    
    TIM2_CCER2 = 0;  
    TIM2_CCMR2 = (6 << 4) | (1 << 3); // PWM1 + preload
    TIM2_CCR2H = 0x02;
    TIM2_CCR2L = 0xBC;    // 700 ? 70%

    TIM2_CCER1 |= (1<<4);      // enable CH2
    TIM2_EGR |= 1;        // update
    TIM2_CR1 |= 1;        // start
}
void delay2_ms(uint32_t time){ //timer 2 delay - 16bit
  TIM2_CR1 = 0;        // disable
  TIM2_EGR |= 1;       // UG: reset CNT + prescaler
  TIM2_CR1 = 1;        // enable
  for(uint32_t t=0;t<time;t++){
    TIM2_SR1 &= ~(1<<0);
    while(!(TIM2_SR1 & 1)); 
  }  
}
void startup_delay(void) {
    delay4_ms(1000);
}

void uart_init(){
  UART1_CR1 = 0;
  UART1_CR2 = 0;
  UART1_CR3 = 0;
  
  UART1_CR1 &= ~(1<<4); //1 start, 8data,M stop
  UART1_CR1 &= ~(1 << 2);  
  UART1_CR3 &= ~(0x3 << 4); 
  UART1_BRR1 = 0x68;
  UART1_BRR2 = 0x03;
  
  
  UART1_CR2 |= (1 << 3);        // TEN
  UART1_CR2 |= (1 << 2);        // REN
  //UART_CR1 |= (1<<5); //enable

}
void uart_putc(uint8_t c){
  while(!(UART1_SR & (1<<7)));
  UART1_DR = c;
}
void uart_puts(uint8_t *string){
  while(*string){
   uart_putc(*string++); 
  }
}
uint8_t uart_getc(){
  while((UART1_SR & (1<<5)) ==1);
  return UART1_DR;
}
void adc_init(){
  ADC_CR1 |= (0<<4);//clock /2
  ADC_CR1 |= (0<<1); //single mode
  ADC_CR2 |=(1<<3); //right align
  ADC_CSR &= ~(0x0F<<0);//channel select
  ADC_CSR |= 0x04;
  ADC_CR1 |= (1<<0);
}
uint8_t adc_complete(){
  return (ADC_CSR & (1<<7));
}
uint32_t last=0;uint32_t lastu=0;
char M[50];
uint16_t adc;
int main( void )
{
  Clock_Cfg(HSI_MODE);
  GPIO_Cfg();
  timer4_init();
  timer2_init();
  //uart_init();
  //adc_init();
  startup_delay();
  __enable_interrupt(); 
  while(1)
  {
    PB_ODR ^= (1<<5);
    delay4_ms(300);
    /*if (SysTick - last >= 200)
    {
      last = SysTick;
      PB_ODR ^= (1<<5);
    }*/
    /*if (SysTick - lastu >= 1000)
    {
      lastu = SysTick;
      uart_puts("Hello World! \n");
      ADC_CR1 |= (1<<0);
      while(adc_complete()==0);
      adc = ((uint8_t)ADC_DRH<<8) | (uint8_t)ADC_DRL;
      sprintf(M,"ADC: %d\n",adc);
      uart_puts((uint8_t*)M);
    }
    */
  }
}
