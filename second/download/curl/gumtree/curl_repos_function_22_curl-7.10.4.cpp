static
size_t write_callback(char *buffer,
                      size_t size,
                      size_t nitems,
                      void *userp)
{
  URL_FILE *url = (URL_FILE *)userp;
  size *= nitems;

  memcpy(url->readptr, buffer, size);
  url->readptr += size;
  url->bytes += size;

  fprintf(stderr, "callback %d size bytes\n", size);

  return size;
}