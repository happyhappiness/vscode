CURLcode curl_read(CURLconnect *c_conn, char *buf, size_t buffersize,
                   size_t *n)
{
  struct connectdata *conn = (struct connectdata *)c_conn;
  struct UrlData *data;
  size_t nread;

  if(!n || !conn || (conn->handle != STRUCT_CONNECT))
    return CURLE_FAILED_INIT;
  data = conn->data;

#ifdef USE_SSLEAY
  if (data->use_ssl) {
    nread = SSL_read (data->ssl, buf, buffersize);
  }
  else {
#endif
    nread = sread (conn->sockfd, buf, buffersize);
#ifdef USE_SSLEAY
  }
#endif /* USE_SSLEAY */
  *n = nread;
  return CURLE_OK;
}