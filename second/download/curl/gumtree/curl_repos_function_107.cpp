int sendf(int fd, struct UrlData *data, char *fmt, ...)
{
  size_t bytes_written;
  char *s;
  va_list ap;
  va_start(ap, fmt);
  s = mvaprintf(fmt, ap);
  va_end(ap);
  if(!s)
    return 0; /* failure */
  if(data->bits.verbose)
    fprintf(data->err, "> %s", s);
#ifndef USE_SSLEAY
   bytes_written = swrite(fd, s, strlen(s));
#else
  if (data->use_ssl) {
    bytes_written = SSL_write(data->ssl, s, strlen(s));
  } else {
    bytes_written = swrite(fd, s, strlen(s));
  }
#endif /* USE_SSLEAY */
  free(s); /* free the output string */
  return(bytes_written);
}