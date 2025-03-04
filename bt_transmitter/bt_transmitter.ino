#include <Arduino.h>
#include <BluetoothA2DPSource.h>
#include <SD.h>
#include <SPI.h>

File audioFile;
BluetoothA2DPSource a2dp_source;

#define SD_CS 5 
bool fileStarted = false;

int32_t get_audio_data(Frame *frame, int32_t frame_count) {
  if (!audioFile) return 0;

  if (!fileStarted) {
    audioFile.seek(44);
    fileStarted = true;
  }

  int bytesRead = audioFile.read((uint8_t *)frame, frame_count * sizeof(Frame));
  if (bytesRead <= 0) {
    Serial.println("End of file, restarting...");
    audioFile.seek(44);
    return 0;
  }

  return bytesRead / sizeof(Frame);
}

void setup() {
  Serial.begin(115200);
  if (!SD.begin(SD_CS)) {
    Serial.println("SD Card Initialization Failed!");
    return;
  }

  audioFile = SD.open("/test_mono.wav", FILE_READ);
  if (!audioFile) {
    Serial.println("Failed to open audio file!");
    return;
  }
  Serial.println("WAV file opened successfully!");
  Serial.println("Starting Bluetooth A2DP Source...");
  a2dp_source.set_auto_reconnect(false);
  a2dp_source.set_data_callback_in_frames(get_audio_data);
  a2dp_source.set_volume(40);
  a2dp_source.start("MyMusic");
}

void loop() {
  delay(1000);
}
