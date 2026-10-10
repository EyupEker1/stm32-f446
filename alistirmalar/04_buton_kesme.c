#include "stm32f446xx.h"

int main(void)
{
    /* 1) Clock'lar */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;       /* LED portu  */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;       /* buton portu */
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;      /* santralci  */

    /* 2) PA5 çıkış */
    GPIOA->MODER &= ~GPIO_MODER_MODER5;
    GPIOA->MODER |=  GPIO_MODER_MODER5_0;

    /* 3) Santralci: 13. hat = Port C */
    SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13;
    SYSCFG->EXTICR[3] |=  SYSCFG_EXTICR4_EXTI13_PC;

    /* 4) Nöbetçi: düşen kenar */
    EXTI->FTSR |= EXTI_FTSR_TR13;

    /* 5) Nöbetçi: 13. hatta izin */
    EXTI->IMR |= EXTI_IMR_MR13;
    EXTI->PR   = EXTI_PR_PR13;       /* başlangıçta eski bayrak kalmasın */

    /* 6) Kapı görevlisi */
    NVIC_EnableIRQ(EXTI15_10_IRQn);

    while (1)
    {
        /* CPU boş, her şey kesmeyle olur */
    }
}

/* 7) Butona basılınca CPU buraya gelir */
void EXTI15_10_IRQHandler(void)
{
    EXTI->PR = EXTI_PR_PR13;                /* bayrağı sil (1 yaz = sil) */

    if (GPIOA->ODR & GPIO_ODR_OD5)
        GPIOA->BSRR = GPIO_BSRR_BR5;        /* söndür */
    else
        GPIOA->BSRR = GPIO_BSRR_BS5;        /* yak */
}
