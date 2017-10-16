  }
}

/* failf() is for messages stating why we failed, the LAST one will be
   returned for the user (if requested) */

void Curl_failf(struct UrlData *data, char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  if(data->errorbuffer)
    vsnprintf(data->errorbuffer, CURL_ERROR_SIZE, fmt, ap);
  else /* no errorbuffer receives this, write to data->err instead */
    vfprintf(data->err, fmt, ap);
  va_end(ap);
}

/* Curl_sendf() sends formated data to the server */
size_t Curl_sendf(int sockfd, struct connectdata *conn,
                  char *fmt, ...)
{
  struct UrlData *data = conn->data;
  size_t bytes_written;
  char *s;
  va_list ap;
  va_start(ap, fmt);
  s = vaprintf(fmt, ap); /* returns an allocated string */
  va_end(ap);
  if(!s)
    return 0; /* failure */
  if(data->bits.verbose)
    fprintf(data->err, "> %s", s);

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
  struct UrlData *data=conn->data; /* conn knows data, not vice versa */

#ifdef USE_SSLEAY
  if (data->ssl.use) {
    int loop=100; /* just a precaution to never loop endlessly */
    while(loop--) {
      bytes_written = SSL_write(data->ssl.handle, mem, len);
      if((-1 != bytes_written) ||
         (SSL_ERROR_WANT_WRITE != SSL_get_error(data->ssl.handle,
                                                bytes_written) ))
        break;
    }
  }
  else {
#endif
#ifdef KRB4
    if(conn->sec_complete) {
      bytes_written = sec_write(conn, sockfd, mem, len);
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

/*
 * External write-function, writes to the data-socket.
 * Takes care of plain sockets, SSL or kerberos transparently.
 */
CURLcode curl_write(CURLconnect *c_conn, char *buf, size_t amount,
                   size_t *n)
{
  struct connectdata *conn = (struct connectdata *)c_conn;

  if(!n || !conn || (conn->handle != STRUCT_CONNECT))
    return CURLE_FAILED_INIT;

  return Curl_write(conn, conn->sockfd, buf, amount, n);
}



/* client_write() sends data to the write callback(s)

   The bit pattern defines to what "streams" to write to. Body and/or header.
   The defines are in sendf.h of course.
 */
CURLcode Curl_client_write(struct UrlData *data,
                           int type,
                           char *ptr,
                           size_t len)
{
  size_t wrote;

  if(0 == len)
    len = strlen(ptr);

