static bool
ConnectionExists(struct SessionHandle *data,
                 struct connectdata *needle,
                 struct connectdata **usethis)
{
  long i;
  struct connectdata *check;
  bool canPipeline = IsPipeliningPossible(data);

  for(i=0; i< data->state.connc->num; i++) {
    bool match = FALSE;
    size_t pipeLen = 0;
    /*
     * Note that if we use a HTTP proxy, we check connections to that
     * proxy and not to the actual remote server.
     */
    check = data->state.connc->connects[i];
    if(!check)
      /* NULL pointer means not filled-in entry */
      continue;

    pipeLen = check->send_pipe->size + check->recv_pipe->size;

    if(check->connectindex == -1) {
      check->connectindex = i; /* Set this appropriately since it might have
                                  been set to -1 when the easy was removed
                                  from the multi */
    }

    if(canPipeline) {
      /* Make sure the pipe has only GET requests */
      struct SessionHandle* sh = gethandleathead(check->send_pipe);
      struct SessionHandle* rh = gethandleathead(check->recv_pipe);
      if(sh) {
        if(!IsPipeliningPossible(sh))
          continue;
      }
      else if(rh) {
        if(!IsPipeliningPossible(rh))
          continue;
      }

#ifdef CURLDEBUG
      if(pipeLen > MAX_PIPELINE_LENGTH) {
        infof(data, "BAD! Connection #%ld has too big pipeline!\n",
              check->connectindex);
      }
#endif
    }
    else {
      if(pipeLen > 0) {
        /* can only happen within multi handles, and means that another easy
           handle is using this connection */
        continue;
      }

#ifdef CURLRES_ASYNCH
      /* ip_addr_str is NULL only if the resolving of the name hasn't completed
         yet and until then we don't re-use this connection */
      if(!check->ip_addr_str) {
        infof(data,
              "Connection #%ld hasn't finished name resolve, can't reuse\n",
              check->connectindex);
        continue;
      }
#endif

      if((check->sock[FIRSTSOCKET] == CURL_SOCKET_BAD) || check->bits.close) {
        /* Don't pick a connection that hasn't connected yet or that is going to
           get closed. */
        infof(data, "Connection #%ld isn't open enough, can't reuse\n",
              check->connectindex);
#ifdef CURLDEBUG
        if(check->recv_pipe->size > 0) {
          infof(data, "BAD! Unconnected #%ld has a non-empty recv pipeline!\n",
                check->connectindex);
        }
#endif
        continue;
      }
    }

    if((needle->protocol&PROT_SSL) != (check->protocol&PROT_SSL))
      /* don't do mixed SSL and non-SSL connections */
      continue;

    if(needle->bits.proxy != check->bits.proxy)
      /* don't do mixed proxy and non-proxy connections */
      continue;

    if(!needle->bits.httpproxy || needle->protocol&PROT_SSL ||
       (needle->bits.httpproxy && check->bits.httpproxy &&
        needle->bits.tunnel_proxy && check->bits.tunnel_proxy &&
        strequal(needle->proxy.name, check->proxy.name) &&
        (needle->port == check->port))) {
      /* The requested connection does not use a HTTP proxy or it uses SSL or
         it is a non-SSL protocol tunneled over the same http proxy name and
         port number */

      if(strequal(needle->protostr, check->protostr) &&
         strequal(needle->host.name, check->host.name) &&
         (needle->remote_port == check->remote_port) ) {
        if(needle->protocol & PROT_SSL) {
          /* This is SSL, verify that we're using the same
             ssl options as well */
          if(!Curl_ssl_config_matches(&needle->ssl_config,
                                      &check->ssl_config)) {
            DEBUGF(infof(data,
                         "Connection #%ld has different SSL parameters, "
                         "can't reuse\n",
                         check->connectindex));
            continue;
          }
          else if(check->ssl[FIRSTSOCKET].state != ssl_connection_complete) {
            DEBUGF(infof(data,
                         "Connection #%ld has not started ssl connect, "
                         "can't reuse\n",
                         check->connectindex));
            continue;
          }
        }
        if((needle->protocol & PROT_FTP) ||
           ((needle->protocol & PROT_HTTP) &&
            (data->state.authhost.want==CURLAUTH_NTLM))) {
          /* This is FTP or HTTP+NTLM, verify that we're using the same name
             and password as well */
          if(!strequal(needle->user, check->user) ||
             !strequal(needle->passwd, check->passwd)) {
            /* one of them was different */
            continue;
          }
        }
        match = TRUE;
      }
    }
    else { /* The requested needle connection is using a proxy,
              is the checked one using the same host, port and type? */
      if(check->bits.proxy &&
         (needle->proxytype == check->proxytype) &&
         strequal(needle->proxy.name, check->proxy.name) &&
         needle->port == check->port) {
        /* This is the same proxy connection, use it! */
        match = TRUE;
      }
    }

    if(match) {
      if(pipeLen == 0) {
        /* The check for a dead socket makes sense only if there
           are no handles in pipeline */
        bool dead = SocketIsDead(check->sock[FIRSTSOCKET]);
        if(dead) {
          check->data = data;
          infof(data, "Connection #%d seems to be dead!\n", i);

          Curl_disconnect(check); /* disconnect resources */
          data->state.connc->connects[i]=NULL; /* nothing here */

          return FALSE;
        }
      }

      check->inuse = TRUE; /* mark this as being in use so that no other
                              handle in a multi stack may nick it */

      *usethis = check;
      return TRUE; /* yes, we found one to use! */
    }
  }

  return FALSE; /* no matching connecting exists */
}