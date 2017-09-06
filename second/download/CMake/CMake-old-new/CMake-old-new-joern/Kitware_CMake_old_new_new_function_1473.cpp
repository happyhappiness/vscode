CURLcode Curl_sendf(int sockfd, struct connectdata *conn,
                    const char *fmt, ...)
{
  struct SessionHandle *data = conn->data;
  ssize_t bytes_written;
  ssize_t write_len;
  CURLcode res;
  char *s;
  char *sptr;
  va_list ap;
  va_start(ap, fmt);
  s = vaprintf(fmt, ap); /* returns an allocated string */
  va_end(ap);
  if(!s)
    return CURLE_OUT_OF_MEMORY; /* failure */

  bytes_written=0;
  write_len = strlen(s);
  sptr = s;

  do {
    /* Write the buffer to the socket */
    res = Curl_write(conn, sockfd, sptr, write_len, &bytes_written);

    if(CURLE_OK != res)
      break;

    if(data->set.verbose)
      Curl_debug(data, CURLINFO_DATA_OUT, sptr, bytes_written);

    if(bytes_written != write_len) {
      /* if not all was written at once, we must advance the pointer, decrease
         the size left and try again! */
      write_len -= bytes_written;
      sptr += bytes_written;
    }
    else
      break;

  } while(1);

  free(s); /* free the output string */

  return res;
}