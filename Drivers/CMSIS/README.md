# Drivers/CMSIS — ST'nin resmi CMSIS basliklari

Register isimlerini (`TIM2->PSC`, `RCC->APB1ENR`, `TIM_CR1_CEN` ...) tanimlayan sadece baslik dosyalaridir.
Kod icermez, HAL degildir. Elle yazilan `#define` adreslerinin yerini alir.

| Klasor | Kaynak | Surum |
|---|---|---|
| `Include/` | [STMicroelectronics/cmsis_core](https://github.com/STMicroelectronics/cmsis_core) | tag `v5.9.0_20250520` (CMSIS Core v5.9.0, ST modified) |
| `Device/ST/STM32F4xx/Include/` | [STMicroelectronics/cmsis_device_f4](https://github.com/STMicroelectronics/cmsis_device_f4) | V2.6.11 etiketinden 2 commit sonrasi (commit `a833f4a`) |

Not: `a833f4a`, `v2.6.11` etiketi degil, deponun o gunku ucu (HEAD). `Include/` klasoru etiketle
bosluk yoksayilarak karsilastirildi, fark yok (tek fark `IRQn_Type` hizalamasi). Etiketten sonraki
diger degisiklik `Source/Templates/system_stm32f4xx.c` icinde, o dosya burada yok.
Etiketle bayt bayt ayni dosya istenirse: `git checkout v2.6.11` ile kopyala.

Surum cifti bilerek secildi: cmsis_device_f4 README'si core/device surumlerinin tutarli olmasini sart kosuyor,
V2.6.11 notu CMSIS Core v5.9.0 ile eslesiyor. `cmsis_core` deposunun varsayilan dali CMSIS 6.1'dir, onu kullanma.

Lisanslar: her klasorde `LICENSE.md` (Apache-2.0). Dosyalara dokunulmadi.

## CubeIDE'ye baglama
Proje Properties -> C/C++ Build -> Settings -> MCU/MCU GCC Compiler -> Include paths:
- `${ProjectDirPath}/../Drivers/CMSIS/Include`
- `${ProjectDirPath}/../Drivers/CMSIS/Device/ST/STM32F4xx/Include`

Kodda: `#include "stm32f446xx.h"`
