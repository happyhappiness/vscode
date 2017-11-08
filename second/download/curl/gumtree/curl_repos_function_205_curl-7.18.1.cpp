static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t  amount = nmemb * size; /* Total bytes curl wants */
  size_t  available = sizeof data - current_offset;  /* What we have to give */
  size_t  given = amount < available ? amount : available; /* What is given */
  (void)stream;
  memcpy(ptr, data + current_offset, given);
  current_offset += given;
  return given;
}