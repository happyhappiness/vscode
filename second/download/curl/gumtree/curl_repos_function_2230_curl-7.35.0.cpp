CURLcode
Curl_gtls_connect(struct connectdata *conn,
                  int sockindex)

{
  CURLcode retcode;
  bool done = FALSE;

  retcode = gtls_connect_common(conn, sockindex, FALSE, &done);
  if(retcode)
    return retcode;

  DEBUGASSERT(done);

  return CURLE_OK;
}