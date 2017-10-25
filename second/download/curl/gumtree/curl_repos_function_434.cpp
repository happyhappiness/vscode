CURLcode Curl_done(struct connectdata **connp,
                   CURLcode status) /* an error if this is called after an
                                       error was detected */
{
  CURLcode result;
  struct connectdata *conn = *connp;
  struct SessionHandle *data=conn->data;

  /* cleanups done even if the connection is re-used */
  if(conn->bits.rangestringalloc) {
    free(conn->range);
    conn->bits.rangestringalloc = FALSE;
  }

  if(conn->dns_entry) {
    Curl_resolv_unlock(data, conn->dns_entry); /* done with this */
    conn->dns_entry = NULL;
  }

  /* Cleanup possible redirect junk */
  if(conn->newurl) {
    free(conn->newurl);
    conn->newurl = NULL;
  }

  /* this calls the protocol-specific function pointer previously set */
  if(conn->curl_done)
    result = conn->curl_done(conn, status);
  else
    result = CURLE_OK;

  Curl_pgrsDone(conn); /* done with the operation */

  /* if data->set.reuse_forbid is TRUE, it means the libcurl client has
     forced us to close this no matter what we think.

     if conn->bits.close is TRUE, it means that the connection should be
     closed in spite of all our efforts to be nice, due to protocol
     restrictions in our or the server's end */
  if(data->set.reuse_forbid || conn->bits.close) {
    CURLcode res2;
    res2 = Curl_disconnect(conn); /* close the connection */

    *connp = NULL; /* to make the caller of this function better detect that
                      this was actually killed here */

    /* If we had an error already, make sure we return that one. But
       if we got a new error, return that. */
    if(!result && res2)
      result = res2;
  }
  else
    infof(data, "Connection #%ld to host %s left intact\n",
          conn->connectindex,
          conn->bits.httpproxy?conn->proxy.dispname:conn->host.dispname);

  return result;
}