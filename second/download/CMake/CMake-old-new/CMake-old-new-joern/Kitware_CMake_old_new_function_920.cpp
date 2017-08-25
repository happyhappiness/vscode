CURLcode Curl_ftpsendf(struct connectdata *conn,
                       const char *fmt, ...)
{
  ssize_t bytes_written;
  char s[256];
  ssize_t write_len;
  char *sptr=s;
  CURLcode res = CURLE_OK;

  va_list ap;
  va_start(ap, fmt);
  vsnprintf(s, 250, fmt, ap);
  va_end(ap);

  if(conn->data->set.verbose)
    fprintf(conn->data->set.err, "> %s\n", s);

  strcat(s, "\r\n"); /* append a trailing CRLF */

  bytes_written=0;
  write_len = strlen(s);

  do {
    res = Curl_write(conn, conn->firstsocket, sptr, write_len,
                     &bytes_written);

    if(CURLE_OK != res)
      break;

    if(bytes_written != write_len) {
      write_len -= bytes_written;
      sptr += bytes_written;
    }
    else
      break;
  } while(1);

  return res;
}