{
    *out++ = hex[digest[i] >> 4];
    *out++ = hex[digest[i] & 0xF];
  }