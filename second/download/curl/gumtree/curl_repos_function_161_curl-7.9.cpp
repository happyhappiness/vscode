CURLcode Curl_connect(struct SessionHandle *data,
                      struct connectdata **in_connect,
                      bool allow_port)
{
  CURLcode code;
  struct connectdata *conn;

  /* call the stuff that needs to be called */
  code = Connect(data, in_connect, allow_port);

  if(CURLE_OK != code) {
    /* We're not allowed to return failure with memory left allocated
       in the connectdata struct, free those here */
    conn = (struct connectdata *)*in_connect;
    if(conn) {
      Curl_disconnect(conn);      /* close the connection */
      *in_connect = NULL;         /* return a NULL */
    }
  }
  return code;
}