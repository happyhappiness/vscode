unsigned long long Curl_read64_le(unsigned char *buf)
{
  return ((unsigned long long)buf[0]) |
         ((unsigned long long)buf[1] << 8) |
         ((unsigned long long)buf[2] << 16) |
         ((unsigned long long)buf[3] << 24) |
         ((unsigned long long)buf[4] << 32) |
         ((unsigned long long)buf[5] << 40) |
         ((unsigned long long)buf[6] << 48) |
         ((unsigned long long)buf[7] << 56);
}