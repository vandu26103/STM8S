#include "gpio.h"
void GPIO_Init(GPIO_TypeDef *GPIOx,uint8_t pin,GPIO_Mode mode){
    switch(mode)
    {
        case INPUT_FLOATING:
            GPIOx->DDR &= ~pins;
            GPIOx->CR1 &= ~pins;
            break;

        case INPUT_PULLUP:
            GPIOx->DDR &= ~pins;
            GPIOx->CR1 |= pins;
            break;

        case OUTPUT_OPENDRAIN:
            GPIOx->DDR |= pins;
            GPIOx->CR1 &= ~pins;
            break;

        case OUTPUT_PUSHPULL:
            GPIOx->DDR |= pins;
            GPIOx->CR1 |= pins;
            break;
    }

    GPIOx->CR2 &= ~pins;
}
void GPIO_SetPin(GPIO_TypeDef *GPIOx,uint8_t pin, uint8_t mode){
    if(mode==0){
        GPIOx->ODR &= ~pin;
    } else {
        GPIOx->ODR |= pin;
    }
}
void GPIO_TogglePin(GPIO_TypeDef *GPIOx,uint8_t pin){
    GPIOx->ODR ^= pin;
}
uint8_t GPIO_Read(GPIO_TypeDef *GPIOx, uint8_t pin){
    return (GPIOx->IDR & pin) ? 1 : 0;
}