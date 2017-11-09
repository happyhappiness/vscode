static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp)
{
  struct input *i = userp;
  size_t retcode = fread(ptr, size, nmemb, i->in);
  i->bytes_read += retcode;
  return retcode;
}