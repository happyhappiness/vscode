char *Curl_memdup(const char *src, size_t length)
{
  char *buffer = malloc(length);
  if(!buffer)
    return NULL; /* fail */

  memcpy(buffer, src, length);

  return buffer;
}