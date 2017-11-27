static int BMP085_detect(void) {
  __s32 res;
  char errbuf[1024];

  if (ioctl(i2c_bus_fd, I2C_SLAVE_FORCE, BMP085_I2C_ADDRESS) < 0) {
    ERROR("barometer: BMP085_detect - problem setting i2c slave address to "
          "0x%02X: %s",
          BMP085_I2C_ADDRESS, sstrerror(errno, errbuf, sizeof(errbuf)));
    return 0;
  }

  res = i2c_smbus_read_byte_data(i2c_bus_fd, BMP085_ADDR_ID_REG);
  if (res == BMP085_CHIP_ID) {
    DEBUG("barometer: BMP085_detect - positive detection");

    /* get version */
    res = i2c_smbus_read_byte_data(i2c_bus_fd, BMP085_ADDR_VERSION);
    if (res < 0) {
      ERROR("barometer: BMP085_detect - problem checking chip version: %s",
            sstrerror(errno, errbuf, sizeof(errbuf)));
      return 0;
    }
    DEBUG("barometer: BMP085_detect - chip version ML:0x%02X AL:0x%02X",
          res & 0x0f, (res & 0xf0) >> 4);
    return 1;
  }

  DEBUG("barometer: BMP085_detect - negative detection");
  return 0;
}