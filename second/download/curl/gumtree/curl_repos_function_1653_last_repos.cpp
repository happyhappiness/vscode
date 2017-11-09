unsigned short Curl_read16_le(const unsigned char *buf)
{
  return (unsigned short)(((unsigned short)buf[0]) |
                          ((unsigned short)buf[1] << 8));
}