static int MPL115_collectd_barometer_read(void) {
  int result = 0;

  double pressure = 0.0;
  double temperature = 0.0;
  double norm_pressure = 0.0;

  value_list_t vl = VALUE_LIST_INIT;
  value_t values[1];

  DEBUG("barometer: MPL115_collectd_barometer_read");

  if (!configured) {
    return -1;
  }

  /* Rather than delaying init, we will intitialize during first read. This
     way at least we have a better chance to have the reference temperature
     already available. */
  if (!avg_initialized) {
    for (int i = 0; i < config_oversample - 1; ++i) {
      result = MPL115_read_averaged(&pressure, &temperature);
      if (result) {
        ERROR("barometer: MPL115_collectd_barometer_read - mpl115 read, "
              "ignored during init");
      }
      DEBUG("barometer: MPL115_collectd_barometer_read - init %d / %d", i + 1,
            config_oversample - 1);
      usleep(20000);
    }
    avg_initialized = 1;
  }

  result = MPL115_read_averaged(&pressure, &temperature);
  if (result)
    return result;

  norm_pressure = abs_to_mean_sea_level_pressure(pressure);

  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, "barometer", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, "mpl115", sizeof(vl.plugin_instance));

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