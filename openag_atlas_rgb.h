/** 
 *  \file openag_atlas_rgb.h
 *  \brief Illuminance and light spectrum rgb sensor.
 */
#ifndef OPENAG_ATLAS_RGB
#define OPENAG_ATLAS_RGB

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif


/**
 * \brief Illuminance, light spectrum rgb sensor.
 */
class AtlasRgb {
 public:
  // Public Functions
  AtlasRgb(String illuminance_id, String light_spectrum_rgb_id, int serial_port);
  void begin(void);
  String get(String id);
  String set (String id, String value);

  // Public Variables
  int illuminance;
  int red;
  int green;
  int blue;
  
 private:
  // Private Functions
  void getSensors(void);

  // Private Variables
  boolean _sensor_failure;
  String _illuminance_id;
  String _light_spectrum_rgb_id;
  int _serial_port;
  HardwareSerial *_port;
};

#endif