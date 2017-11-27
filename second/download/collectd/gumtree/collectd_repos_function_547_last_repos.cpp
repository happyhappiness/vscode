static int MPL3115_collectd_barometer_read(void) {
  int result = 0;

  double pressure = 0.0;
  double temperature = 0.0;
  double norm_pressure = 0.0;

  value_list_t vl = VALUE_LIST_INIT;
  value_t values[1];

  DEBUG("barometer: MPL3115_collectd_barometer_read");

  if (!configured) {
    return -1;
  }

  result = MPL3115_read(&pressure, &temperature);
  if (result)
    return result;

  norm_pressure = abs_to_mean_sea_level_pressure(pressure);

  sstrncpy(vl.plugin, "barometer", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, "mpl3115", sizeof(vl.plugin_instance));

  vl.values_len = 1;
  vl.values = values;

  /* dispatch normalized air pressure */
  sstrncpy(vl.type, "pressure", sizeof(vl.type));
  sstrncpy(vl.type_instance, "normalized", sizeof(vl.type_instance));
  values[0].gauge = norm_pressure;
  plugin_dispatch_values(&vl);

  /* dispatch absolute air pressure */
  sstrncpy(vl.type, "pressure", sizeof(vl.type));
  sstrncpy(vl.type_instance, "absolute", sizeof(vl.type_instance));
  values[0].gauge = pressure;
  plugin_dispatch_values(&vl);

  /* dispatch sensor temperature */
  sstrncpy(vl.type, "temperature", sizeof(vl.type));
  sstrncpy(vl.type_instance, "", sizeof(vl.type_instance));
  values[0].gauge = temperature;
  plugin_dispatch_values(&vl);

  return 0;
}