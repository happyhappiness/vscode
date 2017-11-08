CURLcode
Curl_Transfer(struct connectdata *c_conn, /* connection data */
              int sockindex,       /* socket index to read from or -1 */
              curl_off_t size,     /* -1 if unknown at this point */
              bool getheader,      /* TRUE if header parsing is wanted */
              curl_off_t *bytecountp, /* return number of bytes read or NULL */
              int writesockindex,  /* socket index to write to, it may very
                                      well be the same we read from. -1
                                      disables */
              curl_off_t *writecountp /* return number of bytes written or
                                       NULL */
              )
{
  struct connectdata *conn = (struct connectdata *)c_conn;
  if(!conn)
    return CURLE_BAD_FUNCTION_ARGUMENT;

  curlassert((sockindex <= 1) && (sockindex >= -1));

  /* now copy all input parameters */
  conn->sockfd = sockindex==-1?
    CURL_SOCKET_BAD:conn->sock[sockindex];
  conn->size = size;
  conn->bits.getheader = getheader;
  conn->bytecountp = bytecountp;
  conn->writesockfd = writesockindex==-1?
    CURL_SOCKET_BAD:conn->sock[writesockindex];
  conn->writebytecountp = writecountp;

  return CURLE_OK;

}