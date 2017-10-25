static void ssl_tls_trace(int direction, int ssl_ver, int content_type,
                          const void *buf, size_t len, const SSL *ssl,
                          struct connectdata *conn)
{
  struct SessionHandle *data;
  const char *msg_name, *tls_rt_name;
  char ssl_buf[1024];
  int  ver, msg_type, txt_len;

  if (!conn || !conn->data || !conn->data->set.fdebug ||
      (direction != 0 && direction != 1))
    return;

  data = conn->data;
  ssl_ver >>= 8;
  ver = (ssl_ver == SSL2_VERSION_MAJOR ? '2' :
         ssl_ver == SSL3_VERSION_MAJOR ? '3' : '?');

  /* SSLv2 doesn't seem to have TLS record-type headers, so OpenSSL
   * always pass-up content-type as 0. But the interesting message-type
   * is at 'buf[0]'.
   */
  if (ssl_ver == SSL3_VERSION_MAJOR && content_type != 0)
    tls_rt_name = tls_rt_type(content_type);
  else
    tls_rt_name = "";

  msg_type = *(char*)buf;
  msg_name = ssl_msg_type(ssl_ver, msg_type);

  txt_len = 1 + snprintf(ssl_buf, sizeof(ssl_buf), "SSLv%c, %s%s (%d):\n",
                         ver, tls_rt_name, msg_name, msg_type);
  Curl_debug(data, CURLINFO_TEXT, ssl_buf, txt_len, NULL);

  Curl_debug(data, (direction == 1) ? CURLINFO_SSL_DATA_OUT :
             CURLINFO_SSL_DATA_IN, (char *)buf, len, NULL);
  (void) ssl;
}