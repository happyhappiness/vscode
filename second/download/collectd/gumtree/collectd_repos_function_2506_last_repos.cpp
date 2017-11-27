static uint16_t be16toh(uint16_t n) {
  uint8_t tmp[2];
  memmove(tmp, &n, sizeof(tmp));

  return ((uint16_t)tmp[0] << 8) | ((uint16_t)tmp[1] << 0);
}