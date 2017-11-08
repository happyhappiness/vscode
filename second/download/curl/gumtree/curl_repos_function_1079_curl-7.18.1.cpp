ssize_t Curl_gtls_send(struct connectdata *conn,
                   int sockindex,
                   void *mem,
                   size_t len)
{
  ssize_t rc = gnutls_record_send(conn->ssl[sockindex].session, mem, len);

  if(rc < 0 ) {
    if(rc == GNUTLS_E_AGAIN)
      return 0; /* EWOULDBLOCK equivalent */
    rc = -1; /* generic error code for send failure */
  }

  return rc;
}