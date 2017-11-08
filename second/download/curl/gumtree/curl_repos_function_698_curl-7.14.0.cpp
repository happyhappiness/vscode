int Curl_gtls_send(struct connectdata *conn,
                   int sockindex,
                   void *mem,
                   size_t len)
{
  int rc;
  rc = gnutls_record_send(conn->ssl[sockindex].session, mem, len);

  return rc;
}