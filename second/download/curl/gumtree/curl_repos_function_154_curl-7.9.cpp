CURLcode Curl_disconnect(struct connectdata *conn)
{
  if(!conn)
    return CURLE_OK; /* this is closed and fine already */

  /*
   * The range string is usually freed in curl_done(), but we might
   * get here *instead* if we fail prematurely. Thus we need to be able
   * to free this resource here as well.
   */
  if(conn->bits.rangestringalloc) {
    free(conn->range);
    conn->bits.rangestringalloc = FALSE;
  }

  if(-1 != conn->connectindex) {
    /* unlink ourselves! */
    infof(conn->data, "Closing live connection (#%d)\n", conn->connectindex);
    conn->data->state.connects[conn->connectindex] = NULL;
  }

  if(conn->curl_disconnect)
    /* This is set if protocol-specific cleanups should be made */
    conn->curl_disconnect(conn);

  if(conn->proto.generic)
    free(conn->proto.generic);

#ifdef ENABLE_IPV6
  if(conn->hp) /* host name info */
    freeaddrinfo(conn->hp);
#else
  if(conn->hostent_buf) /* host name info */
    free(conn->hostent_buf);
#endif

  if(conn->newurl)
    free(conn->newurl);

  if(conn->path) /* the URL path part */
    free(conn->path);

#ifdef USE_SSLEAY
  Curl_SSL_Close(conn);
#endif /* USE_SSLEAY */

  /* close possibly still open sockets */
  if(-1 != conn->secondarysocket)
    sclose(conn->secondarysocket);
  if(-1 != conn->firstsocket)
    sclose(conn->firstsocket);

  if(conn->allocptr.proxyuserpwd)
    free(conn->allocptr.proxyuserpwd);
  if(conn->allocptr.uagent)
    free(conn->allocptr.uagent);
  if(conn->allocptr.userpwd)
    free(conn->allocptr.userpwd);
  if(conn->allocptr.rangeline)
    free(conn->allocptr.rangeline);
  if(conn->allocptr.ref)
    free(conn->allocptr.ref);
  if(conn->allocptr.cookie)
    free(conn->allocptr.cookie);
  if(conn->allocptr.host)
    free(conn->allocptr.host);

  if(conn->proxyhost)
    free(conn->proxyhost);

  free(conn); /* free all the connection oriented data */

  return CURLE_OK;
}