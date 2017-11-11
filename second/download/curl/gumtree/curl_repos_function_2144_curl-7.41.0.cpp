static ssize_t gskit_send(struct connectdata *conn, int sockindex,
                           const void *mem, size_t len, CURLcode *curlcode)
{
  struct SessionHandle *data = conn->data;
  CURLcode cc;
  int written;

  cc = gskit_status(data,
                    gsk_secure_soc_write(conn->ssl[sockindex].handle,
                                         (char *) mem, (int) len, &written),
                    "gsk_secure_soc_write()", CURLE_SEND_ERROR);
  if(cc != CURLE_OK) {
    *curlcode = cc;
    written = -1;
  }
  return (ssize_t) written; /* number of bytes */
}