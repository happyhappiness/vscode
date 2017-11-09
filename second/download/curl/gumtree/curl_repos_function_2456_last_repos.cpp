static size_t Curl_gskit_version(char *buffer, size_t size)
{
  strncpy(buffer, "GSKit", size);
  return strlen(buffer);
}