size_t Curl_ftpsendf(int fd, struct connectdata *conn,
                     const char *fmt, ...)
{
  size_t bytes_written;
  char s[256];

  va_list ap;
  va_start(ap, fmt);
  vsnprintf(s, 250, fmt, ap);
  va_end(ap);

  if(conn->data->set.verbose)
    fprintf(conn->data->set.err, "> %s\n", s);

  strcat(s, "\r\n"); /* append a trailing CRLF */

  bytes_written=0;
  Curl_write(conn, fd, s, strlen(s), &bytes_written);

  return(bytes_written);
}