unsigned int Curl_read32_be(unsigned char *buf)
{
  return ((unsigned int)buf[0] << 24) | ((unsigned int)buf[1] << 16) |
         ((unsigned int)buf[2] << 8) | ((unsigned int)buf[3]);
}