CURLcode curl_write(CURLconnect *c_conn, char *buf, size_t amount,
                   size_t *n)
{
  struct connectdata *conn = (struct connectdata *)c_conn;
  struct UrlData *data;
  size_t bytes_written;

  if(!n || !conn || (conn->handle != STRUCT_CONNECT))
    return CURLE_FAILED_INIT;
  data = conn->data;

#ifdef USE_SSLEAY
  if (data->use_ssl) {
    bytes_written = SSL_write(data->ssl, buf, amount);
  }
  else {
#endif
    bytes_written = swrite(conn->writesockfd, buf, amount);
#ifdef USE_SSLEAY
  }
#endif /* USE_SSLEAY */

  *n = bytes_written;
  return CURLE_OK;
}