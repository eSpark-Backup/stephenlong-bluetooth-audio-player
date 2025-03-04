  #include "ESP_I2S.h"
  #include <BluetoothA2DPSink.h>

  #define I2S_BCK         26  // Bit Clock (BCK)
  #define I2S_WS          25  // Word Select (WS/LRCK)
  #define I2S_DOUT        22  // Data Output (DOUT)

  I2SClass i2s;
  BluetoothA2DPSink a2dp_sink(i2s);

  void setup() {
    Serial.begin(115200);

    i2s.setPins(I2S_BCK, I2S_WS, I2S_DOUT);
    if (!i2s.begin(I2S_MODE_STD, 44100, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO, I2S_STD_SLOT_LEFT)) {
      Serial.println("Failed to initialize I2S!");
      while (1); // do nothing
    }

    Serial.println("Starting A2DP Sink...");
    a2dp_sink.start("MyMusic");
  }

  void loop() {
  }
