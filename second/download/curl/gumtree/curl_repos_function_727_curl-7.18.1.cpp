CURLcode Curl_do_more(struct connectdata *conn)
{
  CURLcode result=CURLE_OK;

  if(conn->handler->do_more)
    result = conn->handler->do_more(conn);

  if(result == CURLE_OK)
    /* do_complete must be called after the protocol-specific DO function */
    do_complete(conn);

  return result;
}