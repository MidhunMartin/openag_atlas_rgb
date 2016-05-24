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

#include <openag_peripheral.h>

/**
 * \brief Illuminance, light spectrum rgb sensor.
 */
class AtlasRgb : public Peripheral {
  public:
    // Public variables
    String id;
    int illuminance;
    int red;
    int green;
    int blue;

    // Public functions
    AtlasRgb(String id, String* parameters);
    ~AtlasRgb();
    void begin();
    String get(String key);
    String set (String key, String value);

  private:
    // Private variables
    String _illuminance_message;
    String _light_spectrum_rgb_message;
    uint32_t _time_of_last_reading;
    String _illuminance_key;
    String _light_spectrum_rgb_key;
    const static uint32_t _min_update_interval = 2000;
    int _serial_port;
    HardwareSerial *_port;


    // Private functions
    void getData();
    String getIlluminance();
    String getLightSpectrumRgb();
    String getMessage(String key, String value);
    String getErrorMessage(String key);
};

#endif
