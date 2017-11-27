static int MPL3115_read(double *pressure, double *temperature) {
  __s32 res;
  __s32 ctrl;
  __u8 data[MPL3115_NUM_CONV_VALS];
  long int tmp_value = 0;
  char errbuf[1024];

  /* Set Active - activate the device from standby */
  res = i2c_smbus_read_byte_data(i2c_bus_fd, MPL3115_REG_CTRL_REG1);
  if (res < 0) {
    ERROR("barometer: MPL3115_read - cannot read CTRL_REG1: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return 1;
  }
  ctrl = res;
  res = i2c_smbus_write_byte_data(i2c_bus_fd, MPL3115_REG_CTRL_REG1,
                                  ctrl | MPL3115_CTRL_REG1_SBYB);
  if (res < 0) {
    ERROR("barometer: MPL3115_read - problem activating: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return 1;
  }

  /* base sleep is 5ms x OST */
  usleep(5000 * config_oversample);

  /* check the flags/status if ready */
  res = i2c_smbus_read_byte_data(i2c_bus_fd, MPL3115_REG_STATUS);
  if (res < 0) {
    ERROR("barometer: MPL3115_read - cannot read status register: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return 1;
  }

  while ((res & MPL3115_DR_STATUS_DR) != MPL3115_DR_STATUS_DR) {
    /* try some extra sleep... */
    usleep(10000);

    /* ... and repeat the check. The conversion has to finish sooner or later.
     */
    res = i2c_smbus_read_byte_data(i2c_bus_fd, MPL3115_REG_STATUS);
    if (res < 0) {
      ERROR("barometer: MPL3115_read - cannot read status register: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      return 1;
    }
  }

  /* Now read all the data in one block. There is address autoincrement. */
  res = i2c_smbus_read_i2c_block_data(i2c_bus_fd, MPL3115_REG_OUT_P_MSB,
                                      MPL3115_NUM_CONV_VALS, data);
  if (res < 0) {
    ERROR("barometer: MPL3115_read - cannot read data registers: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return 1;
  }

  tmp_value = (data[0] << 16) | (data[1] << 8) | data[2];
  *pressure = ((double)tmp_value) / 4.0 / 16.0 / 100.0;
  DEBUG("barometer: MPL3115_read - absolute pressure = %lf hPa", *pressure);

  if (data[3] > 0x7F) {
    data[3] = ~data[3] + 1;
    *temperature = data[3];
    *temperature = -*temperature;
  } else {
    *temperature = data[3];
  }

  *temperature += (double)(data[4]) / 256.0;
  DEBUG("barometer: MPL3115_read - temperature = %lf C", *temperature);

  return 0;
}