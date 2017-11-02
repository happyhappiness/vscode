size_t Curl_polarssl_version(char *buffer, size_t size)
{
  unsigned int version = version_get_number();
  return snprintf(buffer, size, "PolarSSL/%d.%d.%d", version>>24,
                  (version>>16)&0xff, (version>>8)&0xff);
}