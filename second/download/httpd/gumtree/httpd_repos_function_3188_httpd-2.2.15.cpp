int XmlUtf16Encode(int charNum, unsigned short *buf)
{
  if (charNum < 0)
    return 0;
  if (charNum < 0x10000) {
    buf[0] = charNum;
    return 1;
  }
  if (charNum < 0x110000) {
    charNum -= 0x10000;
    buf[0] = (charNum >> 10) + 0xD800;
    buf[1] = (charNum & 0x3FF) + 0xDC00;
    return 2;
  }
  return 0;
}