# Xiaozhi Vision — diymore ESP32-S3 N16R8 CAM

Ta definicja płytki uruchamia pełny firmware [Xiaozhi ESP32](https://github.com/78/xiaozhi-esp32): konfigurację Wi-Fi, asystenta głosowego, przesyłanie audio do usługi Xiaozhi, odtwarzanie odpowiedzi, ekran ST7789V oraz kamerę używaną przez funkcje wizyjne. Nie używa karty microSD ani GPIO 38, dlatego nie ma konfliktu z liniami SD na płytce.

## Potwierdzona konfiguracja

| Element | Sygnał | GPIO ESP32-S3 |
| --- | --- | ---: |
| INMP441 | WS / LRCLK | 1 |
| INMP441 | SCK / BCLK | 2 |
| INMP441 | SD | 42 |
| MAX98357A | DIN | 39 |
| MAX98357A | BCLK | 40 |
| MAX98357A | LRC | 41 |
| ST7789V GMT020-02-7P | SCLK | 19 |
| ST7789V GMT020-02-7P | MOSI / SDA | 20 |
| ST7789V GMT020-02-7P | RST | 21 |
| ST7789V GMT020-02-7P | CS | 45 |
| ST7789V GMT020-02-7P | DC | 47 |
| Kamera DVP | zgodnie z wbudowaną taśmą | 4–18, zgodnie z `config.h` |

Podłącz **L/R mikrofonu INMP441 do GND**, aby wybrać lewy kanał. Podłącz **SD wzmacniacza MAX98357A do 3,3 V**, aby wzmacniacz był zawsze aktywny. Wszystkie moduły muszą mieć wspólną masę. TFT z potwierdzonego modułu ma tylko siedem pinów i **nie ma osobnego BL**.

## Budowanie

Projekt wymaga **ESP-IDF 6.1** oraz pobranych zależności Xiaozhi. Uruchom z katalogu głównego repozytorium:

```bash
python scripts/build.py diymore-esp32s3cam-vision --language pl-PL --wake-word nihaoxiaozhi
```

Wynikowy plik do flashowania to `build/merged-binary.bin`. Flashowanie przez USB-UART CH343P jest wymagane, ponieważ GPIO 19 i GPIO 20 są używane przez wyświetlacz. Po pierwszym uruchomieniu urządzenie tworzy hotspot konfiguracyjny Xiaozhi; po połączeniu z Wi-Fi należy dodać urządzenie w panelu `xiaozhi.me`.

## Celowa rezygnacja z microSD

Wbudowane złącze microSD wykorzystuje GPIO 38–40. Głośnik MAX98357A używa GPIO 39–41, więc współdzielenie microSD i audio nie jest bezpieczne. Definicja płytki nie inicjalizuje SD ani nie przypisuje GPIO 38 do podświetlenia TFT.
