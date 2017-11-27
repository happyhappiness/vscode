static int BMP085_read(double *pressure, double *temperature) {
  __s32 res;
  __u8 measBuff[3];

  long adc_pressure;
  long adc_temperature;

  char errbuf[1024];

  /* start conversion of temperature */
  res = i2c_smbus_write_byte_data(i2c_bus_fd, BMP085_ADDR_CTRL_REG,
                                  BMP085_CMD_CONVERT_TEMP);
  if (res < 0) {
    ERROR("barometer: BMP085_read - problem requesting temperature conversion: "
          "%s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return 1;
  }

  usleep(BMP085_TIME_CNV_TEMP); /* wait for the conversion */

  res =
      i2c_smbus_read_i2c_block_data(i2c_bus_fd, BMP085_ADDR_CONV, 2, measBuff);
  if (res < 0) {
    ERROR("barometer: BMP085_read - problem reading temperature data: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return 1;
  }

  adc_temperature = ((unsigned short)measBuff[0] << 8) + measBuff[1];

  /* get presure */
  res = i2c_smbus_write_byte_data(i2c_bus_fd, BMP085_ADDR_CTRL_REG,
                                  bmp085_cmdCnvPress);
  if (res < 0) {
    ERROR("barometer: BMP085_read - problem requesting pressure conversion: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return 1;
  }

  usleep(bmp085_timeCnvPress); /* wait for the conversion */

  res =
      i2c_smbus_read_i2c_block_data(i2c_bus_fd, BMP085_ADDR_CONV, 3, measBuff);
  if (res < 0) {
    ERROR("barometer: BMP085_read - problem reading pressure data: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return 1;
  }

  adc_pressure = (long)((((ulong)measBuff[0] << 16) |
                         ((ulong)measBuff[1] << 8) | (ulong)measBuff[2]) >>
                        (8 - bmp085_oversampling));

  DEBUG("barometer: BMP085_read - raw pressure ADC value = %ld, "
        "raw temperature ADC value = %ld",
        adc_pressure, adc_temperature);

  BMP085_convert_adc_to_real(adc_pressure, adc_temperature, pressure,
                             temperature);

  return 0;
}