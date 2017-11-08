int XmlUtf8Encode(int c, char *buf)
{
  enum {
    /* minN is minimum legal resulting value for N byte sequence */
    min2 = 0x80,
    min3 = 0x800,
    min4 = 0x10000
  };

  if (c < 0)
    return 0;
  if (c < min2) {
    buf[0] = (c | UTF8_cval1);
    return 1;
  }
  if (c < min3) {
    buf[0] = ((c >> 6) | UTF8_cval2);
    buf[1] = ((c & 0x3f) | 0x80);
    return 2;
  }
  if (c < min4) {
    buf[0] = ((c >> 12) | UTF8_cval3);
    buf[1] = (((c >> 6) & 0x3f) | 0x80);
    buf[2] = ((c & 0x3f) | 0x80);
    return 3;
  }
  if (c < 0x110000) {
    buf[0] = ((c >> 18) | UTF8_cval4);
    buf[1] = (((c >> 12) & 0x3f) | 0x80);
    buf[2] = (((c >> 6) & 0x3f) | 0x80);
    buf[3] = ((c & 0x3f) | 0x80);
    return 4;
  }
  return 0;
}