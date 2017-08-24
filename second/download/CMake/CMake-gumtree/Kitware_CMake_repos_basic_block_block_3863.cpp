{
    unsigned char b = bytes[i];

    bool needs_parity = (((b >> 7) ^ (b >> 6) ^ (b >> 5) ^
                          (b >> 4) ^ (b >> 3) ^ (b >> 2) ^
                          (b >> 1)) & 0x01) == 0;

    if(needs_parity)
      bytes[i] |= 0x01;
    else
      bytes[i] &= 0xfe;
  }