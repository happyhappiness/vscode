CURLcode Curl_done(struct connectdata **connp,
                   CURLcode status,  /* an error if this is called after an
                                        error was detected */
                   bool premature)
{
  CURLcode result;
  struct connectdata *conn;
  struct SessionHandle *data;

  DEBUGASSERT(*connp);

  conn = *connp;
  data = conn->data;

  Curl_expire(data, 0); /* stop timer */

  if(Curl_removeHandleFromPipeline(data, conn->recv_pipe) &&
     conn->readchannel_inuse)
    conn->readchannel_inuse = FALSE;
  if(Curl_removeHandleFromPipeline(data, conn->send_pipe) &&
     conn->writechannel_inuse)
    conn->writechannel_inuse = FALSE;
  Curl_removeHandleFromPipeline(data, conn->pend_pipe);

  if(conn->bits.done ||
     (conn->send_pipe->size + conn->recv_pipe->size != 0 &&
      !data->set.reuse_forbid &&
      !conn->bits.close))
    /* Stop if Curl_done() has already been called or pipeline
       is not empty and we do not have to close connection. */
    return CURLE_OK;

  conn->bits.done = TRUE; /* called just now! */

  /* Cleanup possible redirect junk */
  if(data->req.newurl) {
    free(data->req.newurl);
    data->req.newurl = NULL;
  }

  if(conn->dns_entry) {
    Curl_resolv_unlock(data, conn->dns_entry); /* done with this */
    conn->dns_entry = NULL;
  }

  /* this calls the protocol-specific function pointer previously set */
  if(conn->handler->done)
    result = conn->handler->done(conn, status, premature);
  else
    result = CURLE_OK;

  Curl_pgrsDone(conn); /* done with the operation */

  /* if the transfer was completed in a paused state there can be buffered
     data left to write and then kill */
  if(data->state.tempwrite) {
    free(data->state.tempwrite);
    data->state.tempwrite = NULL;
  }

  /* for ares-using, make sure all possible outstanding requests are properly
     cancelled before we proceed */
  ares_cancel(data->state.areschannel);

  /* if data->set.reuse_forbid is TRUE, it means the libcurl client has
     forced us to close this no matter what we think.

     if conn->bits.close is TRUE, it means that the connection should be
     closed in spite of all our efforts to be nice, due to protocol
     restrictions in our or the server's end

     if premature is TRUE, it means this connection was said to be DONE before
     the entire request operation is complete and thus we can't know in what
     state it is for re-using, so we're forced to close it. In a perfect world
     we can add code that keep track of if we really must close it here or not,
     but currently we have no such detail knowledge.
  */
  if(data->set.reuse_forbid || conn->bits.close || premature) {
    CURLcode res2 = Curl_disconnect(conn); /* close the connection */

    /* If we had an error already, make sure we return that one. But
       if we got a new error, return that. */
    if(!result && res2)
      result = res2;
  }
  else {
    ConnectionDone(conn); /* the connection is no longer in use */

    /* remember the most recently used connection */
    data->state.lastconnect = conn->connectindex;

    infof(data, "Connection #%ld to host %s left intact\n",
          conn->connectindex,
          conn->bits.httpproxy?conn->proxy.dispname:conn->host.dispname);
  }

  *connp = NULL; /* to make the caller of this function better detect that
                    this was either closed or handed over to the connection
                    cache here, and therefore cannot be used from this point on
                 */

  return result;
}