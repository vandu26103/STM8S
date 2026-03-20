#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define GPIOA ((GPIO_TypeDef*)0x5000)
#define GPIOB ((GPIO_TypeDef*)0x5005)
#define GPIOC ((GPIO_TypeDef*)0x500A)
#define GPIOD ((GPIO_TypeDef*)0x500F)

#define PIN0 (1<<0)
#define PIN1 (1<<1)
#define PIN2 (1<<2)
#define PIN3 (1<<3)
#define PIN4 (1<<4)
#define PIN5 (1<<5)
#define PIN6 (1<<6)
#define PIN7 (1<<7)

typedef enum {
    INPUT_FLOATING = 0,
    INPUT_PULLUP,
    OUTPUT_OPENDRAIN,
    OUTPUT_PUSHPULL
} GPIO_Mode;

typedef struct {
    volatile uint8_t ODR;
    volatile uint8_t IDR;
    volatile uint8_t DDR;
    volatile uint8_t CR1;
    volatile uint8_t CR2;
} GPIO_TypeDef;


void GPIO_Init(GPIO_TypeDef *GPIOx,uint8_t pin,GPIO_Mode mode);
void GPIO_SetPin(GPIO_TypeDef *GPIOx,uint8_t pin, uint8_t mode);
void GPIO_TogglePin(GPIO_TypeDef *GPIOx,uint8_t pin);
uint8_t GPIO_Read(GPIO_TypeDef *GPIOx, uint8_t pin);




#endif