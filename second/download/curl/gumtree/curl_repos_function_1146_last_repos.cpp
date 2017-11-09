CURLcode Curl_async_resolved(struct connectdata *conn,
                             bool *protocol_done)
{
  CURLcode result;

  if(conn->async.dns) {
    conn->dns_entry = conn->async.dns;
    conn->async.dns = NULL;
  }

  result = Curl_setup_conn(conn, protocol_done);

  if(result)
    /* We're not allowed to return failure with memory left allocated
       in the connectdata struct, free those here */
    Curl_disconnect(conn, FALSE); /* close the connection */

  return result;
}