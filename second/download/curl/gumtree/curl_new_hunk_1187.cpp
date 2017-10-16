  
  return CURLE_OK;
}


/*
 * Internal read-from-socket function. This is meant to deal with plain
 * sockets, SSL sockets and kerberos sockets.
 */
CURLcode Curl_read(struct connectdata *conn, int sockfd,
                   char *buf, size_t buffersize,
                   size_t *n)
{
  struct UrlData *data = conn->data;
  size_t nread;

#ifdef USE_SSLEAY
  if (data->ssl.use) {
    int loop=100; /* just a precaution to never loop endlessly */
    while(loop--) {
      nread = SSL_read(data->ssl.handle, buf, buffersize);
      if((-1 != nread) ||
         (SSL_ERROR_WANT_READ != SSL_get_error(data->ssl.handle, nread) ))
        break;
    }
  }
  else {
#endif
#ifdef KRB4
    if(conn->sec_complete)
      nread = sec_read(conn, sockfd, buf, buffersize);
    else
#endif
      nread = sread (sockfd, buf, buffersize);
#ifdef USE_SSLEAY
  }
#endif /* USE_SSLEAY */
  *n = nread;
  return CURLE_OK;
}

/*
 * The public read function reads from the 'sockfd' file descriptor only.
 * Use the Curl_read() internally when you want to specify fd.
 */

CURLcode curl_read(CURLconnect *c_conn, char *buf, size_t buffersize,
                   size_t *n)
{
  struct connectdata *conn = (struct connectdata *)c_conn;

  if(!n || !conn || (conn->handle != STRUCT_CONNECT))
    return CURLE_FAILED_INIT;

  return Curl_read(conn, conn->sockfd, buf, buffersize, n);
}

