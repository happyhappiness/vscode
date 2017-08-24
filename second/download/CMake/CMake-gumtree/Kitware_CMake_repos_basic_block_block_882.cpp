{
  unsigned char d0, d1, d2, d3;

  d0 = kwsysBase64DecodeChar(src[0]);
  d1 = kwsysBase64DecodeChar(src[1]);
  d2 = kwsysBase64DecodeChar(src[2]);
  d3 = kwsysBase64DecodeChar(src[3]);

  /* Make sure all characters were valid */

  if (d0 == 0xFF || d1 == 0xFF || d2 == 0xFF || d3 == 0xFF) {
    return 0;
  }

  /* Decode the 3 bytes */

  dest[0] = (unsigned char)(((d0 << 2) & 0xFC) | ((d1 >> 4) & 0x03));
  dest[1] = (unsigned char)(((d1 << 4) & 0xF0) | ((d2 >> 2) & 0x0F));
  dest[2] = (unsigned char)(((d2 << 6) & 0xC0) | ((d3 >> 0) & 0x3F));

  /* Return the number of bytes actually decoded */

  if (src[2] == '=') {
    return 1;
  }
  if (src[3] == '=') {
    return 2;
  }
  return 3;
}