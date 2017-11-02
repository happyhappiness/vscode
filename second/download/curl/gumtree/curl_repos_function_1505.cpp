unsigned __int64 Curl_read64_le(unsigned char *buf)
{
  return ((unsigned __int64)buf[0]) | ((unsigned __int64)buf[1] << 8) |
         ((unsigned __int64)buf[2] << 16) | ((unsigned __int64)buf[3] << 24) |
         ((unsigned __int64)buf[4] << 32) | ((unsigned __int64)buf[5] << 40) |
         ((unsigned __int64)buf[6] << 48) | ((unsigned __int64)buf[7] << 56);
}