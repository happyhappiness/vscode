uint128_t str_to_uint128(const char *str, int len) {
  uint128_t lcore_mask;
  int err = 0;

  memset(&lcore_mask, 0, sizeof(lcore_mask));

  if (len <= 2 || strncmp(str, "0x", 2) != 0) {
    ERROR("%s Value %s should be represened in hexadecimal format",
          __FUNCTION__, str);
    return lcore_mask;
  }
  /* If str is <= 64 bit long ('0x' + 16 chars = 18 chars) then
   * conversion is straightforward. Otherwise str is splitted into 64b long
   * blocks */
  if (len <= 18) {
    lcore_mask.low = strtoull_safe(str, &err);
    if (err)
      return lcore_mask;
  } else {
    char low_str[DATA_MAX_NAME_LEN];
    char high_str[DATA_MAX_NAME_LEN];

    memset(high_str, 0, sizeof(high_str));
    memset(low_str, 0, sizeof(low_str));

    strncpy(high_str, str, len - 16);
    strncpy(low_str, str + len - 16, 16);

    lcore_mask.low = strtoull_safe(low_str, &err);
    if (err)
      return lcore_mask;

    lcore_mask.high = strtoull_safe(high_str, &err);
    if (err) {
      lcore_mask.low = 0;
      return lcore_mask;
    }
  }
  return lcore_mask;
}