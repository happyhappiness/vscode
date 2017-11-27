static uint64_t be64toh(uint64_t n) {
  uint8_t tmp[8];
  memmove(tmp, &n, sizeof(tmp));

  return ((uint64_t)tmp[0] << 56) | ((uint64_t)tmp[1] << 48) |
         ((uint64_t)tmp[2] << 40) | ((uint64_t)tmp[3] << 32) |
         ((uint64_t)tmp[4] << 24) | ((uint64_t)tmp[5] << 16) |
         ((uint64_t)tmp[6] << 8) | ((uint64_t)tmp[7] << 0);
}