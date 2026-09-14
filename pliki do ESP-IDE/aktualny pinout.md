
## Potwierdzona konfiguracja

| Element              | Sygnał     | GPIO ESP32-S3|
| ---                  | ---        | ---:         |
| INMP441              | WS / LRCLK |        1     |
| INMP441              | SCK / BCLK |        2     |
| INMP441              | SD         |       42     |
| MAX98357A            | DIN        |       39     |
| MAX98357A            | BCLK       |       40     |
| MAX98357A            | LRC        |       41     |
| ST7789V GMT020-02-7P | SCLK       |       19     |
| ST7789V GMT020-02-7P | MOSI / SDA |       20     |
| ST7789V GMT020-02-7P | RST        |       21     |
| ST7789V GMT020-02-7P | CS         |       45     |
| ST7789V GMT020-02-7P | DC         |       47     |
| WS2811               | DI         |       48     |
| Przycisk Wybudzenia  | BOOT       |        0     |

| Kamera DVP | zgodnie z wbudowaną taśmą | 4–18, zgodnie z `config.h` |

Podłącz **L/R mikrofonu INMP441 do GND**, aby wybrać lewy kanał. Podłącz **SD wzmacniacza MAX98357A do 3,3 V**, aby wzmacniacz był zawsze aktywny. Wszystkie moduły muszą mieć wspólną masę. TFT z potwierdzonego modułu ma tylko siedem pinów i **nie ma osobnego BL**.


```bash
python scripts/build.py diymore-esp32s3cam-vision --language pl-PL
```
