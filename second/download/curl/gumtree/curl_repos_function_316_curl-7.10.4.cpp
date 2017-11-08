int Curl_base64_decode(const char *str, void *data)
{
  int ret;

  base64Decode((unsigned char *)data, (char *)str, &ret);
  return ret;
}