unsigned __int64 Curl_read64_be(unsigned char *buf)
{
  return ((unsigned __int64)buf[0] << 56) | ((unsigned __int64)buf[1] << 48) |
         ((unsigned __int64)buf[2] << 40) | ((unsigned __int64)buf[3] << 32) |
         ((unsigned __int64)buf[4] << 24) | ((unsigned __int64)buf[5] << 16) |
         ((unsigned __int64)buf[6] << 8) | ((unsigned __int64)buf[7]);
}