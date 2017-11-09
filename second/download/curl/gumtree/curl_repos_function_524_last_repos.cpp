static size_t myreadfunc(void *ptr, size_t size, size_t nmemb, void *stream)
{
  static size_t total = POSTLEN;
  static char buf[1024];
  (void)stream;

  memset(buf, 'A', sizeof(buf));

  size *= nmemb;
  if(size > total)
    size = total;

  if(size > sizeof(buf))
    size = sizeof(buf);

  memcpy(ptr, buf, size);
  total -= size;
  return size;
}