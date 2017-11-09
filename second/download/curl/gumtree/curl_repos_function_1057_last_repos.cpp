static CURLcode done_sending(struct connectdata *conn,
                             struct SingleRequest *k)
{
  k->keepon &= ~KEEP_SEND; /* we're done writing */

  Curl_http2_done_sending(conn);

  if(conn->bits.rewindaftersend) {
    CURLcode result = Curl_readrewind(conn);
    if(result)
      return result;
  }
  return CURLE_OK;
}