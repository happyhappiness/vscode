static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t retcode;

  intptr_t fd = (intptr_t)stream;

  retcode = read(fd, ptr, size * nmemb);

  fprintf(stderr, "*** We read %d bytes from file\n", retcode);

  return retcode;
}