CURLcode Curl_async_resolved(struct connectdata *conn,
                             bool *protocol_done)
{
#if defined(USE_ARES) || defined(USE_THREADING_GETHOSTBYNAME) || \
    defined(USE_THREADING_GETADDRINFO)
  CURLcode code = SetupConnection(conn, conn->async.dns, protocol_done);

  if(code)
    /* We're not allowed to return failure with memory left allocated
       in the connectdata struct, free those here */
    Curl_disconnect(conn); /* close the connection */

  return code;
#else
  (void)conn;
  (void)protocol_done;
  return CURLE_OK;
#endif
}