CURLcode Curl_disconnect(struct connectdata *conn)
{
  struct SessionHandle *data;
  if(!conn)
    return CURLE_OK; /* this is closed and fine already */

  data = conn->data;

#if defined(CURLDEBUG) && defined(AGGRESIVE_TEST)
  /* scan for DNS cache entries still marked as in use */
  Curl_hash_apply(data->hostcache,
                  NULL, Curl_scan_cache_used);
#endif

  Curl_hostcache_prune(data); /* kill old DNS cache entries */

  /*
   * The range string is usually freed in curl_done(), but we might
   * get here *instead* if we fail prematurely. Thus we need to be able
   * to free this resource here as well.
   */
  if(conn->bits.rangestringalloc) {
    free(conn->range);
    conn->bits.rangestringalloc = FALSE;
  }

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

  if(conn->curl_disconnect)
    /* This is set if protocol-specific cleanups should be made */
    conn->curl_disconnect(conn);

  if(-1 != conn->connectindex) {
    /* unlink ourselves! */
    infof(data, "Closing connection #%ld\n", conn->connectindex);
    data->state.connects[conn->connectindex] = NULL;
  }

  Curl_safefree(conn->proto.generic);
  Curl_safefree(conn->newurl);
  Curl_safefree(conn->pathbuffer); /* the URL path buffer */

  Curl_safefree(conn->host.rawalloc); /* host name buffer */
  Curl_safefree(conn->proxy.rawalloc); /* proxy name buffer */
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
  Curl_ssl_close(conn);

  /* close possibly still open sockets */
  if(CURL_SOCKET_BAD != conn->sock[SECONDARYSOCKET])
    sclose(conn->sock[SECONDARYSOCKET]);
  if(CURL_SOCKET_BAD != conn->sock[FIRSTSOCKET])
    sclose(conn->sock[FIRSTSOCKET]);

  Curl_safefree(conn->user);
  Curl_safefree(conn->passwd);
  Curl_safefree(conn->proxyuser);
  Curl_safefree(conn->proxypasswd);
  Curl_safefree(conn->allocptr.proxyuserpwd);
  Curl_safefree(conn->allocptr.uagent);
  Curl_safefree(conn->allocptr.userpwd);
  Curl_safefree(conn->allocptr.accept_encoding);
  Curl_safefree(conn->allocptr.rangeline);
  Curl_safefree(conn->allocptr.ref);
  Curl_safefree(conn->allocptr.host);
  Curl_safefree(conn->allocptr.cookiehost);
  Curl_safefree(conn->ip_addr_str);

  /* possible left-overs from the async name resolvers */
#if defined(USE_ARES)
  Curl_safefree(conn->async.hostname);
  Curl_safefree(conn->async.os_specific);
#elif defined(CURLRES_THREADED)
  Curl_destroy_thread_data(&conn->async);
#endif

  Curl_free_ssl_config(&conn->ssl_config);

  free(conn); /* free all the connection oriented data */

  return CURLE_OK;
}