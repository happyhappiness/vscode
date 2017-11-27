static int MPL115_read_averaged(double *pressure, double *temperature) {
  uint8_t mpl115_conv[MPL115_NUM_CONV] = {0};
  int8_t res;
  int retries;
  int conv_pressure;
  int conv_temperature;
  double adc_pressure;
  double adc_temperature;
  char errbuf[1024];

  *pressure = 0.0;
  *temperature = 0.0;

  /* start conversion of both temp and presure */
  retries = MPL115_CONVERSION_RETRIES;
  while (retries > 0) {
    /* write 1 to start conversion */
    res = i2c_smbus_write_byte_data(i2c_bus_fd, MPL115_CMD_CONVERT_BOTH, 0x01);
    if (res >= 0)
      break;

    --retries;
    if (retries > 0) {
      ERROR("barometer: MPL115_read_averaged - requesting conversion: %s, "
            "will retry at most %d more times",
            sstrerror(errno, errbuf, sizeof(errbuf)), retries);
    } else {
      ERROR("barometer: MPL115_read_averaged - requesting conversion: %s, "
            "too many failed retries",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      return -1;
    }
  }

  usleep(10000); /* wait 10ms for the conversion */

  retries = MPL115_CONVERSION_RETRIES;
  while (retries > 0) {
    res = i2c_smbus_read_i2c_block_data(i2c_bus_fd, MPL115_ADDR_CONV,
                                        STATIC_ARRAY_SIZE(mpl115_conv),
                                        mpl115_conv);
    if (res >= 0)
      break;

    --retries;
    if (retries > 0) {
      ERROR("barometer: MPL115_read_averaged - reading conversion: %s, "
            "will retry at most %d more times",
            sstrerror(errno, errbuf, sizeof(errbuf)), retries);
    } else {
      ERROR("barometer: MPL115_read_averaged - reading conversion: %s, "
            "too many failed retries",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      return -1;
    }
  }

  conv_pressure = ((mpl115_conv[0] << 8) | mpl115_conv[1]) >> 6;
  conv_temperature = ((mpl115_conv[2] << 8) | mpl115_conv[3]) >> 6;
  DEBUG("barometer: MPL115_read_averaged, raw pressure ADC value = %d, "
        "raw temperature ADC value = %d",
        conv_pressure, conv_temperature);

  adc_pressure = averaging_add_sample(&pressure_averaging, conv_pressure);
  adc_temperature =
      averaging_add_sample(&temperature_averaging, conv_temperature);

  MPL115_convert_adc_to_real(adc_pressure, adc_temperature, pressure,
                             temperature);

  DEBUG("barometer: MPL115_read_averaged - averaged ADC pressure = %lf / "
        "temperature = %lf, "
        "real pressure = %lf hPa / temperature = %lf C",
        adc_pressure, adc_temperature, *pressure, *temperature);

  return 0;
}