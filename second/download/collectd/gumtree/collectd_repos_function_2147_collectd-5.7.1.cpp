static int sensors_snprintf_chip_name(char *buf, size_t buf_size,
                                      const sensors_chip_name *chip) {
  int status = -1;

  if (chip->bus == SENSORS_CHIP_NAME_BUS_ISA) {
    status = ssnprintf(buf, buf_size, "%s-isa-%04x", chip->prefix, chip->addr);
  } else if (chip->bus == SENSORS_CHIP_NAME_BUS_DUMMY) {
    status = snprintf(buf, buf_size, "%s-%s-%04x", chip->prefix, chip->busname,
                      chip->addr);
  } else {
    status = snprintf(buf, buf_size, "%s-i2c-%d-%02x", chip->prefix, chip->bus,
                      chip->addr);
  }

  return (status);
}