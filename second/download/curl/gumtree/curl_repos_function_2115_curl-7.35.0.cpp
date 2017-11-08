bool Curl_schannel_data_pending(const struct connectdata *conn, int sockindex)
{
  const struct ssl_connect_data *connssl = &conn->ssl[sockindex];

  if(connssl->use) /* SSL/TLS is in use */
    return (connssl->encdata_offset > 0 ||
            connssl->decdata_offset > 0 ) ? TRUE : FALSE;
  else
    return FALSE;
}