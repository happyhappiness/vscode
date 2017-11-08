unsigned long long Curl_read64_be(unsigned char *buf)
{
  return ((unsigned long long)buf[0] << 56) |
         ((unsigned long long)buf[1] << 48) |
         ((unsigned long long)buf[2] << 40) |
         ((unsigned long long)buf[3] << 32) |
         ((unsigned long long)buf[4] << 24) |
         ((unsigned long long)buf[5] << 16) |
         ((unsigned long long)buf[6] << 8) |
         ((unsigned long long)buf[7]);
}