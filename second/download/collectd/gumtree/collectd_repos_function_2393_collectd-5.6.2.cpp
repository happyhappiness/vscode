double htond(double d) {
  union {
    uint8_t byte[8];
    uint64_t integer;
    double floating;
  } ret;

  if (isnan(d)) {
    ret.byte[0] = ret.byte[1] = ret.byte[2] = ret.byte[3] = 0x00;
    ret.byte[4] = ret.byte[5] = 0x00;
    ret.byte[6] = 0xf8;
    ret.byte[7] = 0x7f;
    return (ret.floating);
  } else {
    uint64_t tmp;

    ret.floating = d;
    tmp = FP_CONVERT(ret.integer);
    ret.integer = tmp;
    return (ret.floating);
  }
}