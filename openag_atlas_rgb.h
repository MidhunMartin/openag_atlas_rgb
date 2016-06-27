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
#include <std_msgs/UInt16.h>
#include <std_msgs/UInt8MultiArray.h>

/**
 * \brief Illuminance, light spectrum rgb sensor.
 */
class AtlasRgb {
  public:
    // Constructor
    AtlasRgb(int serial_port);

    // Public variables
    bool has_error;
    char* error_msg;

    // Public functions
    void begin();
    bool get_light_illuminance(std_msgs::UInt16 &msg);
    bool get_light_spectrum(std_msgs::UInt8MultiArray &msg);

  private:
    // Private variables
    uint16_t _light_illuminance;
    uint8_t _light_spectrum[3];
    uint32_t _time_of_last_reading;
    bool _send_light_illuminance;
    bool _send_light_spectrum;
    const static uint32_t _min_update_interval = 2000;
    HardwareSerial* _serial_port;

    // Private functions
    void update();
    void readData();
};

#endif
