/** 
 *  \file openag_atlas_rgb.cpp
 *  \brief Illuminance and light spectrum rgb sensor.
 */

 #include "openag_atlas_rgb.h"

 AtlasRgb::AtlasRgb(String illuminance_id, String light_spectrum_rgb_id, int serial_port) {
  _illuminance_id = illuminance_id;
  _light_spectrum_rgb_id = light_spectrum_rgb_id;
  _serial_port = serial_port;
}


void AtlasRgb::begin(void) {
  // Assume Sensor Functions
  _sensor_failure = false;
  
  // Set Serial Port
  switch(_serial_port) {
    case 1:
      _port = &Serial1;
      break;
    case 2:
      _port = &Serial2;
      break;
    case 3:
      _port = &Serial3;
      break;
    default:
      _sensor_failure = true;
      return;
  }

  // Open Serial Port
  _port->begin(9600);
  
  // Check Sensor Functions
  _port->print("RESPONSE,1\r"); // enable response code
  String string = Serial3.readStringUntil(13);
  String ok_string = "*OK";
  if (!string.equals(ok_string)) { // check sensor responds *OK
    _sensor_failure = true;
  }
  else {
    // Set Operation Mode
    _port->print("RESPONSE,0\r"); // disable response code
    _port->print("C,0\r"); // disable streaming
    _port->print("O,RGB,1\r"); // enable rgb readings
    _port->print("O,PROX,0\r"); // disable proximity readings
    _port->print("O,LUX,1\r"); // enable lux readings
    _port->print("O,CIE,0\r"); // disable cie readings  

    // Warm Up Sensor
    getSensors();
  }  
}


String AtlasRgb::get(String id) {
  // Check For Failure
    if ((id == _illuminance_id || id == _light_spectrum_rgb_id) && _sensor_failure) {
    return String(id + ":" + "error");
  }

  // Respond To Get
  if (id == _illuminance_id) {
    getSensors();
    return String(id + ":" + String(illuminance));
  }
  else if (id == _light_spectrum_rgb_id) {
    getSensors();
    return String(id + ":" + String(red) + "," + String(green) + "," + String(blue));
  }
}


String AtlasRgb::set(String id, String value) {
  // Check For Failure
  if ((id == _illuminance_id || id == _light_spectrum_rgb_id) && _sensor_failure) {
    return String(id + ":" + "error");
  }
  
  // Respond To Set
  if (id == _illuminance_id) {
    return String(id + ":" + "error");
  }
  else if (id == _light_spectrum_rgb_id) {
    return String(id + ":" + "error");
  }
}


void AtlasRgb::getSensors(void) {
  // Get Raw Data
  Serial3.print("R\r");
  String string = Serial3.readStringUntil(13);

  // Process Red Value
  int start_index = 0;
  int end_index = string.indexOf(',');
  red = string.substring(start_index, end_index).toInt();
  
  // Process Green Value
  start_index = end_index + 1;
  end_index = string.indexOf(',', start_index);
  green = string.substring(start_index, end_index).toInt();
  
  // Process Blue Value
  start_index = end_index + 1;
  end_index = string.indexOf(',', start_index);
  blue = string.substring(start_index, end_index).toInt();

  // Process Illuminance Value
  start_index = end_index + 1; // skip over "Lux"
  end_index = string.indexOf(',', start_index);
  start_index = end_index + 1;
  end_index = string.indexOf(',', start_index);
  illuminance = string.substring(start_index, end_index).toInt();
}