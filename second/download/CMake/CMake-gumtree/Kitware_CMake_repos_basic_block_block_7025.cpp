{
  CURLcode result;
  bool done = FALSE;

  result = polarssl_connect_common(conn, sockindex, FALSE, &done);
  if(result)
    return result;

  DEBUGASSERT(done);

  return CURLE_OK;
}