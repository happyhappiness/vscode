CURLcode Curl_disconnect(struct connectdata *conn)
{
  struct SessionHandle *data;
  if(!conn)
    return CURLE_OK; /* this is closed and fine already */
  data = conn->data;

  if(!data) {
    DEBUGF(infof(data, "DISCONNECT without easy handle, ignoring\n"));
    return CURLE_OK;
  }

#if defined(CURLDEBUG) && defined(AGGRESIVE_TEST)
  /* scan for DNS cache entries still marked as in use */
  Curl_hash_apply(data->hostcache,
                  NULL, Curl_scan_cache_used);
#endif

  Curl_expire(data, 0); /* shut off timers */
  Curl_hostcache_prune(data); /* kill old DNS cache entries */

  if((conn->ntlm.state != NTLMSTATE_NONE) ||
     (conn->proxyntlm.state != NTLMSTATE_NONE)) {
    /* Authentication data is a mix of connection-related and sessionhandle-
       related stuff. NTLM is connection-related so when we close the shop
       we shall forget. */
    data->state.authhost.done = FALSE;
    data->state.authhost.picked =
      data->state.authhost.want;

    data->state.authproxy.done = FALSE;
    data->state.authproxy.picked =
      data->state.authproxy.want;

    data->state.authproblem = FALSE;

    Curl_ntlm_cleanup(conn);
  }

  if(conn->handler->disconnect)
    /* This is set if protocol-specific cleanups should be made */
    conn->handler->disconnect(conn);

  if(-1 != conn->connectindex) {
    /* unlink ourselves! */
    infof(data, "Closing connection #%ld\n", conn->connectindex);
    if(data->state.connc)
      /* only clear the table entry if we still know in which cache we
         used to be in */
      data->state.connc->connects[conn->connectindex] = NULL;
  }

#ifdef USE_LIBIDN
  if(conn->host.encalloc)
    idn_free(conn->host.encalloc); /* encoded host name buffer, must be freed
                                      with idn_free() since this was allocated
                                      by libidn */
  if(conn->proxy.encalloc)
    idn_free(conn->proxy.encalloc); /* encoded proxy name buffer, must be
                                       freed with idn_free() since this was
                                       allocated by libidn */
#endif

  Curl_ssl_close(conn, FIRSTSOCKET);

  /* Indicate to all handles on the pipe that we're dead */
  if(Curl_isPipeliningEnabled(data)) {
    signalPipeClose(conn->send_pipe);
    signalPipeClose(conn->recv_pipe);
    signalPipeClose(conn->pend_pipe);
  }

  conn_free(conn);
  data->state.current_conn = NULL;

  return CURLE_OK;
}