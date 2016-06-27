#include <openag_atlas_rgb.h>

AtlasRgb atlas_rgb_1(3);

void setup() {
  Serial.begin(9600);
  atlas_rgb_1.begin();
}

std_msgs::UInt16 light_illuminance_msg;
std_msgs::UInt8MultiArray light_spectrum_msg;

void loop() {
  if (atlas_rgb_1.get_light_illuminance(light_illuminance_msg)) {
    Serial.print("Light Illuminance: ");
    Serial.println(light_illuminance_msg.data);
  }
  if (atlas_rgb_1.get_light_spectrum(light_spectrum_msg)) {
    Serial.println("Light Spectrum: ");
    Serial.print("  Red:");
    Serial.println(light_spectrum_msg.data[0]);
    Serial.print("  Green:");
    Serial.println(light_spectrum_msg.data[1]);
    Serial.print("  Blue:");
    Serial.println(light_spectrum_msg.data[2]);
  }
  if (atlas_rgb_1.has_error) {
    Serial.print("Error: ");
    Serial.println(atlas_rgb_1.error_msg);
    atlas_rgb_1.has_error = false;
  }
}
