#include "wifi_board.h"
#include "codecs/no_audio_codec.h"
#include "display/lcd_display.h"
#include "application.h"
#include "button.h"
#include "config.h"
#include "esp32_camera.h"
#include "led/single_led.h"

#include <driver/ledc.h>
#include <driver/spi_common.h>
#include <esp_lcd_panel_io.h>
#include <esp_lcd_panel_ops.h>
#include <esp_lcd_panel_vendor.h>
#include <esp_log.h>
#include <esp_psram.h>

#define TAG "DiymoreS3CamVision"

class DiymoreEsp32S3CamVisionBoard : public WifiBoard {
 private:
  Button boot_button_;
  LcdDisplay* display_ = nullptr;
  Esp32Camera* camera_ = nullptr;

  void InitializeSpi() {
    spi_bus_config_t bus_config = {};
    bus_config.mosi_io_num = DISPLAY_MOSI_PIN;
    bus_config.miso_io_num = GPIO_NUM_NC;
    bus_config.sclk_io_num = DISPLAY_CLK_PIN;
    bus_config.quadwp_io_num = GPIO_NUM_NC;
    bus_config.quadhd_io_num = GPIO_NUM_NC;
    bus_config.max_transfer_sz = DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(uint16_t);
    ESP_ERROR_CHECK(spi_bus_initialize(SPI3_HOST, &bus_config, SPI_DMA_CH_AUTO));
  }

  void InitializeDisplay() {
    esp_lcd_panel_io_handle_t panel_io = nullptr;
    esp_lcd_panel_handle_t panel = nullptr;

    esp_lcd_panel_io_spi_config_t io_config = {};
    io_config.cs_gpio_num = DISPLAY_CS_PIN;
    io_config.dc_gpio_num = DISPLAY_DC_PIN;
    io_config.spi_mode = DISPLAY_SPI_MODE;
    io_config.pclk_hz = 40 * 1000 * 1000;
    io_config.trans_queue_depth = 10;
    io_config.lcd_cmd_bits = 8;
    io_config.lcd_param_bits = 8;
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi(SPI3_HOST, &io_config, &panel_io));

    esp_lcd_panel_dev_config_t panel_config = {};
    panel_config.reset_gpio_num = DISPLAY_RST_PIN;
    panel_config.rgb_ele_order = DISPLAY_RGB_ORDER;
    panel_config.bits_per_pixel = 16;
    ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(panel_io, &panel_config, &panel));
    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel));
    ESP_ERROR_CHECK(esp_lcd_panel_invert_color(panel, DISPLAY_INVERT_COLOR));
    ESP_ERROR_CHECK(esp_lcd_panel_swap_xy(panel, DISPLAY_SWAP_XY));
    ESP_ERROR_CHECK(esp_lcd_panel_mirror(panel, DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y));

    display_ = new SpiLcdDisplay(panel_io, panel, DISPLAY_WIDTH, DISPLAY_HEIGHT,
                                 DISPLAY_OFFSET_X, DISPLAY_OFFSET_Y,
                                 DISPLAY_MIRROR_X, DISPLAY_MIRROR_Y,
                                 DISPLAY_SWAP_XY);
  }

  void InitializeCamera() {
    if (!esp_psram_is_initialized()) {
      ESP_LOGE(TAG, "OPI PSRAM is unavailable; camera and wake word require PSRAM");
      return;
    }

    camera_config_t config = {};
    config.pin_pwdn = CAMERA_PIN_PWDN;
    config.pin_reset = CAMERA_PIN_RESET;
    config.pin_xclk = CAMERA_PIN_XCLK;
    config.pin_sccb_sda = CAMERA_PIN_SIOD;
    config.pin_sccb_scl = CAMERA_PIN_SIOC;
    config.pin_d7 = CAMERA_PIN_D7;
    config.pin_d6 = CAMERA_PIN_D6;
    config.pin_d5 = CAMERA_PIN_D5;
    config.pin_d4 = CAMERA_PIN_D4;
    config.pin_d3 = CAMERA_PIN_D3;
    config.pin_d2 = CAMERA_PIN_D2;
    config.pin_d1 = CAMERA_PIN_D1;
    config.pin_d0 = CAMERA_PIN_D0;
    config.pin_vsync = CAMERA_PIN_VSYNC;
    config.pin_href = CAMERA_PIN_HREF;
    config.pin_pclk = CAMERA_PIN_PCLK;
    config.xclk_freq_hz = CAMERA_XCLK_FREQ_HZ;
    config.ledc_timer = LEDC_TIMER_0;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.pixel_format = PIXFORMAT_RGB565;
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 2;
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.grab_mode = CAMERA_GRAB_LATEST;

    camera_ = new Esp32Camera(config);
  }

  void InitializeButtons() {
    boot_button_.OnClick([this]() {
      auto& app = Application::GetInstance();
      if (app.GetDeviceState() == kDeviceStateStarting) {
        EnterWifiConfigMode();
        return;
      }
      app.ToggleChatState();
    });
  }

 public:
  DiymoreEsp32S3CamVisionBoard() : boot_button_(BOOT_BUTTON_GPIO) {
    InitializeSpi();
    InitializeDisplay();
    InitializeButtons();
    InitializeCamera();
  }

  Led* GetLed() override {
    static SingleLed led(BUILTIN_LED_GPIO);
    return &led;
  }

  AudioCodec* GetAudioCodec() override {
    static NoAudioCodecSimplex audio_codec(
        AUDIO_INPUT_SAMPLE_RATE, AUDIO_OUTPUT_SAMPLE_RATE,
        AUDIO_I2S_SPK_GPIO_BCLK, AUDIO_I2S_SPK_GPIO_LRCK,
        AUDIO_I2S_SPK_GPIO_DOUT, AUDIO_I2S_MIC_GPIO_SCK,
        AUDIO_I2S_MIC_GPIO_WS, AUDIO_I2S_MIC_GPIO_DIN);
    return &audio_codec;
  }

  Display* GetDisplay() override {
    return display_;
  }

  Camera* GetCamera() override {
    return camera_;
  }
};

DECLARE_BOARD(DiymoreEsp32S3CamVisionBoard);
