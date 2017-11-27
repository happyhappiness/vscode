static double ntohd(double val) /* {{{ */
{
  static int config = 0;

  union {
    uint8_t byte[8];
    double floating;
  } in = {
      .floating = val,
  };
  union {
    uint8_t byte[8];
    double floating;
  } out = {
      .byte = {0},
  };

  if (config == 0) {
    double d = 8.642135e130;
    uint8_t b[8];

    memcpy(b, &d, sizeof(b));

    if ((b[0] == 0x2f) && (b[1] == 0x25) && (b[2] == 0xc0) && (b[3] == 0xc7) &&
        (b[4] == 0x43) && (b[5] == 0x2b) && (b[6] == 0x1f) && (b[7] == 0x5b))
      config = 1; /* need nothing */
    else if ((b[7] == 0x2f) && (b[6] == 0x25) && (b[5] == 0xc0) &&
             (b[4] == 0xc7) && (b[3] == 0x43) && (b[2] == 0x2b) &&
             (b[1] == 0x1f) && (b[0] == 0x5b))
      config = 2; /* endian flip */
    else if ((b[4] == 0x2f) && (b[5] == 0x25) && (b[6] == 0xc0) &&
             (b[7] == 0xc7) && (b[0] == 0x43) && (b[1] == 0x2b) &&
             (b[2] == 0x1f) && (b[3] == 0x5b))
      config = 3; /* int swap */
    else
      config = 4;
  }

  if (memcmp((char[]){0, 0, 0, 0, 0, 0, 0xf8, 0x7f}, in.byte, 8) == 0