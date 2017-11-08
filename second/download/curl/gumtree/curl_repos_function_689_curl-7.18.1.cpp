static void conn_free(struct connectdata *conn)
{
  if(!conn)
    return;

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
  Curl_safefree(conn->trailer);
  Curl_safefree(conn->host.rawalloc); /* host name buffer */
  Curl_safefree(conn->proxy.rawalloc); /* proxy name buffer */
  Curl_safefree(conn->master_buffer);

  Curl_llist_destroy(conn->send_pipe, NULL);
  Curl_llist_destroy(conn->recv_pipe, NULL);
  Curl_llist_destroy(conn->pend_pipe, NULL);

  /* possible left-overs from the async name resolvers */
#if defined(USE_ARES)
  Curl_safefree(conn->async.hostname);
  Curl_safefree(conn->async.os_specific);
#elif defined(CURLRES_THREADED)
  Curl_destroy_thread_data(&conn->async);
#endif

  Curl_ssl_close(conn, FIRSTSOCKET);
  Curl_ssl_close(conn, SECONDARYSOCKET);

  Curl_free_ssl_config(&conn->ssl_config);

  free(conn); /* free all the connection oriented data */
}