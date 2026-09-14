#ifndef DIYMORE_ESP32S3CAM_VISION_CONFIG_H
#define DIYMORE_ESP32S3CAM_VISION_CONFIG_H

#include <driver/gpio.h>

// INMP441 (input) and MAX98357A (output) use independent I2S controllers.
#define AUDIO_INPUT_SAMPLE_RATE   16000
#define AUDIO_OUTPUT_SAMPLE_RATE  24000
#define AUDIO_I2S_METHOD_SIMPLEX

// INMP441: WS -> GPIO1, SCK -> GPIO2, SD -> GPIO42.
#define AUDIO_I2S_MIC_GPIO_WS     GPIO_NUM_1
#define AUDIO_I2S_MIC_GPIO_SCK    GPIO_NUM_2
#define AUDIO_I2S_MIC_GPIO_DIN    GPIO_NUM_42

// MAX98357A: DIN -> GPIO39, BCLK -> GPIO40, LRC -> GPIO41.
#define AUDIO_I2S_SPK_GPIO_DOUT   GPIO_NUM_39
#define AUDIO_I2S_SPK_GPIO_BCLK   GPIO_NUM_40
#define AUDIO_I2S_SPK_GPIO_LRCK   GPIO_NUM_41

#define BUILTIN_LED_GPIO          GPIO_NUM_48
#define BOOT_BUTTON_GPIO          GPIO_NUM_0

// On-board OV3660/OV5640-compatible parallel camera bus.
#define CAMERA_PIN_PWDN           GPIO_NUM_NC
#define CAMERA_PIN_RESET          GPIO_NUM_NC
#define CAMERA_PIN_XCLK           GPIO_NUM_15
#define CAMERA_PIN_SIOD           GPIO_NUM_4
#define CAMERA_PIN_SIOC           GPIO_NUM_5
#define CAMERA_PIN_D7             GPIO_NUM_16  // Y9
#define CAMERA_PIN_D6             GPIO_NUM_17  // Y8
#define CAMERA_PIN_D5             GPIO_NUM_18  // Y7
#define CAMERA_PIN_D4             GPIO_NUM_12  // Y6
#define CAMERA_PIN_D3             GPIO_NUM_10  // Y5
#define CAMERA_PIN_D2             GPIO_NUM_8   // Y4
#define CAMERA_PIN_D1             GPIO_NUM_9   // Y3
#define CAMERA_PIN_D0             GPIO_NUM_11  // Y2
#define CAMERA_PIN_VSYNC          GPIO_NUM_6
#define CAMERA_PIN_HREF           GPIO_NUM_7
#define CAMERA_PIN_PCLK           GPIO_NUM_13
#define CAMERA_XCLK_FREQ_HZ       20000000

// GMT020-02-7P ST7789V, 7-pin module without a BL connection.
#define DISPLAY_MOSI_PIN          GPIO_NUM_20
#define DISPLAY_CLK_PIN           GPIO_NUM_19
#define DISPLAY_DC_PIN            GPIO_NUM_47
#define DISPLAY_RST_PIN           GPIO_NUM_21
#define DISPLAY_CS_PIN            GPIO_NUM_45
#define DISPLAY_BACKLIGHT_PIN     GPIO_NUM_NC

// The panel is physically 240x320. These settings reproduce Adafruit
// tft.setRotation(1): a 320x240 landscape Xiaozhi interface.
#define DISPLAY_WIDTH             320
#define DISPLAY_HEIGHT            240
#define DISPLAY_OFFSET_X          0
#define DISPLAY_OFFSET_Y          0
#define DISPLAY_MIRROR_X          true
#define DISPLAY_MIRROR_Y          false
#define DISPLAY_SWAP_XY           true
#define DISPLAY_INVERT_COLOR      true
#define DISPLAY_RGB_ORDER         LCD_RGB_ELEMENT_ORDER_RGB
#define DISPLAY_SPI_MODE          0

#endif  // DIYMORE_ESP32S3CAM_VISION_CONFIG_H
