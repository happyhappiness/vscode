CURLcode Curl_do(struct connectdata *conn)
{
  CURLcode result=CURLE_OK;

  if(conn->curl_do)
    /* generic protocol-specific function pointer set in curl_connect() */
    result = conn->curl_do(conn);

  return result;
}