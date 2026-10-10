/*
 * main.c — NUCLEO-F446RE, register seviyesinde LED blink
 * LD2 = PA5, pin HIGH olunca yanar (UM1724).
 * Pin BSRR ile suruluyor: atomik, okuma gerektirmiyor.
 */

#include <stdint.h>

#define RCC_AHB1ENR (*(volatile uint32_t *)(0x40023830UL))  /* base 0x40023800 + 0x30 */
#define GPIOA_MODER (*(volatile uint32_t *)(0x40020000UL))  /* base 0x40020000 + 0x00 */
#define GPIOA_BSRR  (*(volatile uint32_t *)(0x40020018UL))  /* base 0x40020000 + 0x18 */

#define LED_PIN 5u

int main(void)
{
    /* Clock acilmazsa yazma sessizce kaybolur, hata vermez. Ilk suphelin burasi. */
    RCC_AHB1ENR |= (1u << 0);

    /* Her pine 2 bit dustugu icin kaydirma LED_PIN*2. Once temizle, sonra yaz. */
    GPIOA_MODER &= ~(3u << (LED_PIN * 2));
    GPIOA_MODER |=  (1u << (LED_PIN * 2));   /* 01 = cikis */

    while (1)
    {
        /* "=" bilincli: 0 yazilan bite dokunulmaz, okumaya gerek yok.
         * |= yazmak BSRR'yi kullanma sebebini yok eder. */
        GPIOA_BSRR = (1u << LED_PIN);           /* BS5 -> yak */
        for (volatile int i = 0; i < 500000; i++);

        GPIOA_BSRR = (1u << (LED_PIN + 16));    /* BR5 -> sondur */
        for (volatile int i = 0; i < 500000; i++);
    }
}

/* TODO(H4): bos dongu gecikmesi saat hizina bagimli. SysTick ile degistirilecek. */
