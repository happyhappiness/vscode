CURLcode Curl_do_more(struct connectdata *conn)
{
  CURLcode result=CURLE_OK;

  if(conn->curl_do_more)
    result = conn->curl_do_more(conn);

  return result;
}