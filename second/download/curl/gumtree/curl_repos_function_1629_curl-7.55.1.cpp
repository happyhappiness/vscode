unsigned short Curl_read16_be(const unsigned char *buf)
{
  return (unsigned short)(((unsigned short)buf[0] << 8) |
                          ((unsigned short)buf[1]));
}