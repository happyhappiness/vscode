static int collectd_barometer_config(const char *key, const char *value) {
  DEBUG("barometer: collectd_barometer_config");

  if (strcasecmp(key, "Device") == 0) {
    sfree(config_device);
    config_device = strdup(value);
  } else if (strcasecmp(key, "Oversampling") == 0) {
    int oversampling_tmp = atoi(value);
    if (oversampling_tmp < 1 || oversampling_tmp > 1024) {
      WARNING("barometer: collectd_barometer_config: invalid oversampling: %d."
              " Allowed values are 1 to 1024 (for MPL115) or 1 to 128 (for "
              "MPL3115) or 1 to 8 (for BMP085).",
              oversampling_tmp);
      return 1;
    }
    config_oversample = oversampling_tmp;
  } else if (strcasecmp(key, "Altitude") == 0) {
    config_altitude = atof(value);
  } else if (strcasecmp(key, "Normalization") == 0) {
    int normalize_tmp = atoi(value);
    if (normalize_tmp < 0 || normalize_tmp > 2) {
      WARNING("barometer: collectd_barometer_config: invalid normalization: %d",
              normalize_tmp);
      return 1;
    }
    config_normalize = normalize_tmp;
  } else if (strcasecmp(key, "TemperatureSensor") == 0) {
    if (temp_list_add(temp_list, value)) {
      return -1;
    }
  } else if (strcasecmp(key, "PressureOffset") == 0) {
    config_press_offset = atof(value);
  } else if (strcasecmp(key, "TemperatureOffset") == 0) {
    config_temp_offset = atof(value);
  } else {
    return -1;
  }

  return 0;
}