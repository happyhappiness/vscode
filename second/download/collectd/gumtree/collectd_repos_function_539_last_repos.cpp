static int BMP085_read_coeffs(void) {
  __s32 res;
  __u8 coeffs[BMP085_NUM_COEFFS];
  char errbuf[1024];

  res = i2c_smbus_read_i2c_block_data(i2c_bus_fd, BMP085_ADDR_COEFFS,
                                      BMP085_NUM_COEFFS, coeffs);
  if (res < 0) {
    ERROR("barometer: BMP085_read_coeffs - problem reading data: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  bmp085_AC1 = ((int16_t)coeffs[0] << 8) | (int16_t)coeffs[1];
  bmp085_AC2 = ((int16_t)coeffs[2] << 8) | (int16_t)coeffs[3];
  bmp085_AC3 = ((int16_t)coeffs[4] << 8) | (int16_t)coeffs[5];
  bmp085_AC4 = ((uint16_t)coeffs[6] << 8) | (uint16_t)coeffs[7];
  bmp085_AC5 = ((uint16_t)coeffs[8] << 8) | (uint16_t)coeffs[9];
  bmp085_AC6 = ((uint16_t)coeffs[10] << 8) | (uint16_t)coeffs[11];
  bmp085_B1 = ((int16_t)coeffs[12] << 8) | (int16_t)coeffs[13];
  bmp085_B2 = ((int16_t)coeffs[14] << 8) | (int16_t)coeffs[15];
  bmp085_MB = ((int16_t)coeffs[16] << 8) | (int16_t)coeffs[17];
  bmp085_MC = ((int16_t)coeffs[18] << 8) | (int16_t)coeffs[19];
  bmp085_MD = ((int16_t)coeffs[20] << 8) | (int16_t)coeffs[21];

  DEBUG("barometer: BMP085_read_coeffs - AC1=%d, AC2=%d, AC3=%d, AC4=%u,"
        " AC5=%u, AC6=%u, B1=%d, B2=%d, MB=%d, MC=%d, MD=%d",
        bmp085_AC1, bmp085_AC2, bmp085_AC3, bmp085_AC4, bmp085_AC5, bmp085_AC6,
        bmp085_B1, bmp085_B2, bmp085_MB, bmp085_MC, bmp085_MD);

  return 0;
}