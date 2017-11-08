size_t Curl_qsossl_version(char * buffer, size_t size)

{
  strncpy(buffer, "IBM OS/400 SSL", size);
  return strlen(buffer);
}