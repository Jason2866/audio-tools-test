#define HELIX_LOGGING_ACTIVE false
#include "AudioTools.h"
#include "AudioTools/AudioLibs/A2DPStream.h"
//#include "AudioTools/AudioLibs/AudioSourceSDFAT.h"
#include "AudioTools/Disk/LegacyAudioSourceSDFAT.h"
#include "AudioTools/AudioCodecs/CodecMP3Helix.h"

const char *startFilePath="/music/";
const char* ext="mp3";
AudioSourceSDFAT source(startFilePath, ext, 15);
A2DPStream out;
MP3DecoderHelix decoder;
AudioPlayer player(source, out, decoder);

void setup() {
  Serial.begin(115200);
  AudioToolsLogger.begin(Serial, AudioToolsLogLevel::Warning);
  // setup player
  // Setting up SPI if necessary with the right SD pins by calling 
  SPI.begin(14, 12, 13, 15);
  player.setVolume(0.8);
  player.begin();

  // setup output - We send the test signal via A2DP - so we conect to a Bluetooth Speaker
  auto cfg = out.defaultConfig(TX_MODE);
  cfg.silence_on_nodata = true; // prevent disconnect when there is no audio data
  cfg.name = "CLIP 5";  // set the device here. Otherwise the first available device is used for output
  //cfg.auto_reconnect = true;  // if this is use we just quickly connect to the last device ignoring cfg.name
  out.begin(cfg);
}

void loop() {
  player.copy();
}
