CURLcode Curl_sendf(int sockfd, struct connectdata *conn,
                    const char *fmt, ...)
{
  struct SessionHandle *data = conn->data;
  ssize_t bytes_written;
  CURLcode result;
  char *s;
  va_list ap;
  va_start(ap, fmt);
  s = vaprintf(fmt, ap); /* returns an allocated string */
  va_end(ap);
  if(!s)
    return 0; /* failure */
  if(data->set.verbose)
    fprintf(data->set.err, "> %s", s);

  /* Write the buffer to the socket */
  result = Curl_write(conn, sockfd, s, strlen(s), &bytes_written);

  free(s); /* free the output string */

  return result;
}