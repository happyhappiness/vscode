(i = 0; i < 8; ++i)
    data[i] = (md5_byte_t)(pms->count[i >> 2] >> ((i & 3) << 3))