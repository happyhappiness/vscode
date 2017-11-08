static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *stream)
{
  ssize_t retcode;
  curl_off_t nread;

  int *fdp = (int *)stream;
  int fd = *fdp;

  retcode = read(fd, ptr, size * nmemb);

  nread = (curl_off_t)retcode;

  fprintf(stderr, "*** We read %" CURL_FORMAT_CURL_OFF_T
          " bytes from file\n", nread);

  return retcode;
}