static int collectd_barometer_shutdown(void) {
  DEBUG("barometer: collectd_barometer_shutdown");

  if (sensor_type == Sensor_MPL115) {
    averaging_delete(&pressure_averaging);
    averaging_delete(&temperature_averaging);

    temp_list_delete(&temp_list);
  }

  if (i2c_bus_fd > 0) {
    close(i2c_bus_fd);
    i2c_bus_fd = -1;
    sfree(config_device);
  }

  return 0;
}