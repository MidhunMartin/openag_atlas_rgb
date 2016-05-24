/**
 *  \file openag_atlas_rgb.cpp
 *  \brief Illuminance and light spectrum rgb sensor.
 */

 #include "openag_atlas_rgb.h"

 AtlasRgb::AtlasRgb(String id, String* parameters) : Peripheral(id, parameters) {
   this->id = id;
  _serial_port = parameters[0].toInt();
  _illuminance_key = "illuminance";
  _light_spectrum_rgb_key = "light_spectrum_rgb";
}

AtlasRgb::~AtlasRgb() {}

void AtlasRgb::begin(void) {
  _time_of_last_reading = 0;
  // Select serial port
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
  }

  // Enable serial port
  _port->begin(9600);

  // Set operation modes
  _port->print("RESPONSE,0\r"); // disable response code
  _port->print("C,0\r"); // disable streaming
  _port->print("O,RGB,1\r"); // enable rgb readings
  _port->print("O,PROX,0\r"); // disable proximity readings
  _port->print("O,LUX,1\r"); // enable lux readings
  _port->print("O,CIE,0\r"); // disable cie readings
  _port->print("RESPONSE,1\r"); // enable response code
  _port->readStringUntil(13);
}

  // Check For Failure
  // _port->print("RESPONSE,1\r"); // enable response code
  // String string = Serial3.readStringUntil(13);
  // String ok_string = "*OK";
  // if (!string.equals(ok_string)) { // check sensor responds *OK
  //   _sensor_failure = true;
  // }
  // else {
  // }

  // String(id + ":" + String(red) + "," + String(green) + "," + String(blue));

String AtlasRgb::get(String key) {
  if (key == _illuminance_key) {
    return getIlluminance();
  }
  else if (key == _light_spectrum_rgb_key) {
    return getLightSpectrumRgb();
  }
  return getErrorMessage(key);
}

String AtlasRgb::set(String key, String value) {
  return getErrorMessage(key);
}

String AtlasRgb::getIlluminance() {
  if (millis() - _time_of_last_reading > _min_update_interval){ // can only read sensor so often
    getData();
    _time_of_last_reading = millis();
  }
  return _illuminance_message;
}

String AtlasRgb::getLightSpectrumRgb() {
  if (millis() - _time_of_last_reading > _min_update_interval){ // can only read sensor so often
    getData();
    _time_of_last_reading = millis();
  }
  return _light_spectrum_rgb_message;
}

void AtlasRgb::getData() {
  boolean is_good_reading = true;

  // Read sensor
  _port->print("R\r");
  String response = _port->readStringUntil(13);
  String data_string = _port->readStringUntil(13);

  // Check for failure
  String ok_string = "*OK";
  if (!response.equals(ok_string)) {
    is_good_reading = false;
  }
  else {
    // Process red value
    int start_index = 0;
    int end_index = data_string.indexOf(',');
    red = data_string.substring(start_index, end_index).toInt();

    // Process green value
    start_index = end_index + 1;
    end_index = data_string.indexOf(',', start_index);
    green = data_string.substring(start_index, end_index).toInt();

    // Process blue value
    start_index = end_index + 1;
    end_index = data_string.indexOf(',', start_index);
    blue = data_string.substring(start_index, end_index).toInt();

    // Process illuminance value
    start_index = end_index + 1; // skip over "Lux"
    end_index = data_string.indexOf(',', start_index);
    start_index = end_index + 1;
    end_index = data_string.indexOf(',', start_index);
    illuminance = data_string.substring(start_index, end_index).toInt();
  }

  // Update messages
  if (is_good_reading) {
    _illuminance_message = getMessage(_illuminance_key, String(illuminance));
    String value = "(" + String(red) + "," + String(green) + "," + String(blue) + ")";
    _light_spectrum_rgb_message = getMessage(_light_spectrum_rgb_key, value);
  }
  else { // read failure
    _illuminance_message = getErrorMessage(_illuminance_key);
    _light_spectrum_rgb_message = getErrorMessage(_light_spectrum_rgb_key);
  }
}

String AtlasRgb::getMessage(String key, String value) {
  return String(id + "," + key + "," + value);
}

String AtlasRgb::getErrorMessage(String key) {
  return String(id + "," + key + ",error");
}
