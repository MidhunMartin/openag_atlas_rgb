#include <openag_atlas_rgb.h>

AtlasRgb atlas_rgb("illuminance", "light_spectrum_rgb", 3);

void setup() {
  Serial.begin(9600);
  atlas_rgb.begin();
}

void loop() {
  Serial.println(atlas_rgb.get("illuminance"));
  Serial.println(atlas_rgb.get("light_spectrum_rgb"));
  Serial.println();
  delay(1000);
}