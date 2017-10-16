/* Curl_infof() is for info message along the way */

void Curl_infof(struct SessionHandle *data, const char *fmt, ...)
{
  va_list ap;
  if(data->set.verbose) {
    va_start(ap, fmt);
    fputs("* ", data->set.err);
    vfprintf(data->set.err, fmt, ap);
    va_end(ap);
  }
}

/* Curl_failf() is for messages stating why we failed, the LAST one will be
   returned for the user (if requested) */

void Curl_failf(struct SessionHandle *data, const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  if(data->set.errorbuffer)
    vsnprintf(data->set.errorbuffer, CURL_ERROR_SIZE, fmt, ap);
  va_end(ap);
}

/* Curl_sendf() sends formated data to the server */
size_t Curl_sendf(int sockfd, struct connectdata *conn,
                  const char *fmt, ...)
{
  struct SessionHandle *data = conn->data;
  size_t bytes_written;
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
  Curl_write(conn, sockfd, s, strlen(s), &bytes_written);

  free(s); /* free the output string */

  return bytes_written;
}

/*
 * Curl_write() is an internal write function that sends plain (binary) data
 * to the server. Works with plain sockets, SSL or kerberos.
 *
 */
CURLcode Curl_write(struct connectdata *conn, int sockfd,
                    void *mem, size_t len,
                    size_t *written)
{
  size_t bytes_written;

#ifdef USE_SSLEAY
  /* SSL_write() is said to return 'int' while write() and send() returns
     'size_t' */
  int ssl_bytes;
  if (conn->ssl.use) {
    int loop=100; /* just a precaution to never loop endlessly */
    while(loop--) {
      ssl_bytes = SSL_write(conn->ssl.handle, mem, len);
      if((0 >= ssl_bytes) ||
         (SSL_ERROR_WANT_WRITE != SSL_get_error(conn->ssl.handle,
                                                ssl_bytes) )) {
        /* this converts from signed to unsigned... */
        bytes_written = ssl_bytes;
        break;
      }
    }
  }
  else {
#endif
#ifdef KRB4
    if(conn->sec_complete) {
      bytes_written = Curl_sec_write(conn, sockfd, mem, len);
    }
    else
#endif /* KRB4 */
      bytes_written = swrite(sockfd, mem, len);
#ifdef USE_SSLEAY
  }
#endif

  *written = bytes_written;
  return CURLE_OK;
}

/* client_write() sends data to the write callback(s)

   The bit pattern defines to what "streams" to write to. Body and/or header.
   The defines are in sendf.h of course.
