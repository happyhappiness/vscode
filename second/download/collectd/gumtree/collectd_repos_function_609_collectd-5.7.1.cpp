static enum Sensor_type detect_sensor_type(void) {
  if (BMP085_detect())
    return Sensor_BMP085;

  else if (MPL3115_detect())
    return Sensor_MPL3115;

  else if (MPL115_detect())
    return Sensor_MPL115;

  return Sensor_none;
}