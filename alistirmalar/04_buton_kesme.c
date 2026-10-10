/*
 * 04_buton_kesme.c — NUCLEO-F446RE, alistirma 4
 * B1 (PC13, aktif-dusuk) -> EXTI13 dusen kenar -> NVIC -> EXTI15_10_IRQHandler
 * Her basista LD2 (PA5) durumunu degistirir. Register seviyesi, CMSIS basliklari (HAL yok).
 * Basliklar: Drivers/CMSIS (bkz. Drivers/CMSIS/README.md)
 */

#include "stm32f446xx.h"

int main(void)
{
    /* 1) Clock'lar: kapali birime yazilan sessizce kaybolur */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;       /* LED portu  */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;       /* buton portu */
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;      /* SYSCFG, APB2'de */

    /* 2) PA5 cikis (MODER 01) */
    GPIOA->MODER &= ~GPIO_MODER_MODER5;
    GPIOA->MODER |=  GPIO_MODER_MODER5_0;

    /* 3) SYSCFG: EXTI hat 13 = Port C (EXTICR4 kodda [3]) */
    SYSCFG->EXTICR[3] &= ~SYSCFG_EXTICR4_EXTI13;
    SYSCFG->EXTICR[3] |=  SYSCFG_EXTICR4_EXTI13_PC;

    /* 4) EXTI: basinca pin HIGH->LOW, yani dusen kenar */
    EXTI->FTSR |= EXTI_FTSR_TR13;

    /* 5) EXTI: hat 13'e izin, baslangicta eski bayrak kalmasin */
    EXTI->IMR |= EXTI_IMR_MR13;
    EXTI->PR   = EXTI_PR_PR13;

    /* 6) NVIC: hat 10-15 ortak kapi */
    NVIC_EnableIRQ(EXTI15_10_IRQn);

    while (1)
    {
        /* CPU bos, is kesmeyle yapilir */
    }
}

/* Handler adi startup dosyasindaki vektor tablosuyla harfi harfine ayni olmali */
void EXTI15_10_IRQHandler(void)
{
    EXTI->PR = EXTI_PR_PR13;                   /* bayragi sil: 1 yazmak siler (rc_w1) */

    if (GPIOA->ODR & GPIO_ODR_OD5)
        GPIOA->BSRR = GPIO_BSRR_BR5;           /* yaniksa sondur */
    else
        GPIOA->BSRR = GPIO_BSRR_BS5;           /* sonukse yak */
}
