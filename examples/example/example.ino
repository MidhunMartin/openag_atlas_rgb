#include <openag_atlas_rgb.h>
String parameters[] = {"3"};
AtlasRgb atlas_rgb_1("atlas_rgb_1", parameters);

void setup() {
  Serial.begin(9600);
  atlas_rgb_1.begin();
}

void loop() {
  Serial.println(atlas_rgb_1.get("illuminance"));
  Serial.println(atlas_rgb_1.get("light_spectrum_rgb"));
  Serial.println();
  delay(1000);
}
