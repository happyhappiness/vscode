static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t  amount = nmemb * size; /* Total bytes curl wants */
  if(amount < strlen(data)) {
    return strlen(data);
  }
  (void)stream;
  memcpy(ptr, data, strlen(data));
  return strlen(data);
}