CURLcode Curl_async_resolved(struct connectdata *conn,
                             bool *protocol_done)
{
  CURLcode code;

  if(conn->async.dns) {
    conn->dns_entry = conn->async.dns;
    conn->async.dns = NULL;
  }

  code = Curl_setup_conn(conn, protocol_done);

  if(code)
    /* We're not allowed to return failure with memory left allocated
       in the connectdata struct, free those here */
    Curl_disconnect(conn, FALSE); /* close the connection */

  return code;
}