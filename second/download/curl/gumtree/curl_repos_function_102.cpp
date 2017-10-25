CURLcode curl_do(CURLconnect *in_conn)
{
  struct connectdata *conn = in_conn;
  CURLcode result;

  if(!conn || (conn->handle!= STRUCT_CONNECT)) {
    return CURLE_BAD_FUNCTION_ARGUMENT;
  }
  if(conn->state != CONN_INIT) {
    return CURLE_BAD_CALLING_ORDER;
  }

  if(conn->curl_do) {
    /* generic protocol-specific function pointer set in curl_connect() */
    result = conn->curl_do(conn);
    if(result) {
      conn->state = CONN_ERROR;
      return result;
    }
  }

  conn->state = CONN_DO; /* we have entered this state */

#if 0
  if(conn->bytecount) {
    double ittook = tvdiff (tvnow(), conn->now);
    infof(data, "%i bytes transfered in %.3lf seconds (%.0lf bytes/sec).\n",
          conn->bytecount, ittook, (double)conn->bytecount/(ittook!=0.0?ittook:1));
  }
#endif
  return CURLE_OK;
}