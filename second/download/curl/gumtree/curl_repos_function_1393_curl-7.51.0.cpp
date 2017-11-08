static bool
ConnectionExists(struct Curl_easy *data,
                 struct connectdata *needle,
                 struct connectdata **usethis,
                 bool *force_reuse,
                 bool *waitpipe)
{
  struct connectdata *check;
  struct connectdata *chosen = 0;
  bool foundPendingCandidate = FALSE;
  bool canPipeline = IsPipeliningPossible(data, needle);
  struct connectbundle *bundle;

#ifdef USE_NTLM
  bool wantNTLMhttp = ((data->state.authhost.want &
                      (CURLAUTH_NTLM | CURLAUTH_NTLM_WB)) &&
                      (needle->handler->protocol & PROTO_FAMILY_HTTP));
  bool wantProxyNTLMhttp = (needle->bits.proxy_user_passwd &&
                           ((data->state.authproxy.want &
                           (CURLAUTH_NTLM | CURLAUTH_NTLM_WB)) &&
                           (needle->handler->protocol & PROTO_FAMILY_HTTP)));
#endif

  *force_reuse = FALSE;
  *waitpipe = FALSE;

  /* We can't pipe if the site is blacklisted */
  if(canPipeline && Curl_pipeline_site_blacklisted(data, needle)) {
    canPipeline = FALSE;
  }

  /* Look up the bundle with all the connections to this
     particular host */
  bundle = Curl_conncache_find_bundle(needle, data->state.conn_cache);
  if(bundle) {
    /* Max pipe length is zero (unlimited) for multiplexed connections */
    size_t max_pipe_len = (bundle->multiuse != BUNDLE_MULTIPLEX)?
      max_pipeline_length(data->multi):0;
    size_t best_pipe_len = max_pipe_len;
    struct curl_llist_element *curr;
    const char *hostname;

    if(needle->bits.conn_to_host)
      hostname = needle->conn_to_host.name;
    else
      hostname = needle->host.name;

    infof(data, "Found bundle for host %s: %p [%s]\n",
          hostname, (void *)bundle,
          (bundle->multiuse== BUNDLE_PIPELINING?
           "can pipeline":
           (bundle->multiuse== BUNDLE_MULTIPLEX?
            "can multiplex":"serially")));

    /* We can't pipe if we don't know anything about the server */
    if(canPipeline) {
      if(bundle->multiuse <= BUNDLE_UNKNOWN) {
        if((bundle->multiuse == BUNDLE_UNKNOWN) && data->set.pipewait) {
          infof(data, "Server doesn't support multi-use yet, wait\n");
          *waitpipe = TRUE;
          return FALSE; /* no re-use */
        }

        infof(data, "Server doesn't support multi-use (yet)\n");
        canPipeline = FALSE;
      }
      if((bundle->multiuse == BUNDLE_PIPELINING) &&
         !Curl_pipeline_wanted(data->multi, CURLPIPE_HTTP1)) {
        /* not asked for, switch off */
        infof(data, "Could pipeline, but not asked to!\n");
        canPipeline = FALSE;
      }
      else if((bundle->multiuse == BUNDLE_MULTIPLEX) &&
              !Curl_pipeline_wanted(data->multi, CURLPIPE_MULTIPLEX)) {
        infof(data, "Could multiplex, but not asked to!\n");
        canPipeline = FALSE;
      }
    }

    curr = bundle->conn_list->head;
    while(curr) {
      bool match = FALSE;
      size_t pipeLen;

      /*
       * Note that if we use a HTTP proxy in normal mode (no tunneling), we
       * check connections to that proxy and not to the actual remote server.
       */
      check = curr->ptr;
      curr = curr->next;

      if(disconnect_if_dead(check, data))
        continue;

      pipeLen = check->send_pipe->size + check->recv_pipe->size;

      if(canPipeline) {
        if(check->bits.protoconnstart && check->bits.close)
          continue;

        if(!check->bits.multiplex) {
          /* If not multiplexing, make sure the pipe has only GET requests */
          struct Curl_easy* sh = gethandleathead(check->send_pipe);
          struct Curl_easy* rh = gethandleathead(check->recv_pipe);
          if(sh) {
            if(!IsPipeliningPossible(sh, check))
              continue;
          }
          else if(rh) {
            if(!IsPipeliningPossible(rh, check))
              continue;
          }
        }
      }
      else {
        if(pipeLen > 0) {
          /* can only happen within multi handles, and means that another easy
             handle is using this connection */
          continue;
        }

        if(Curl_resolver_asynch()) {
          /* ip_addr_str[0] is NUL only if the resolving of the name hasn't
             completed yet and until then we don't re-use this connection */
          if(!check->ip_addr_str[0]) {
            infof(data,
                  "Connection #%ld is still name resolving, can't reuse\n",
                  check->connection_id);
            continue;
          }
        }

        if((check->sock[FIRSTSOCKET] == CURL_SOCKET_BAD) ||
           check->bits.close) {
          if(!check->bits.close)
            foundPendingCandidate = TRUE;
          /* Don't pick a connection that hasn't connected yet or that is going
             to get closed. */
          infof(data, "Connection #%ld isn't open enough, can't reuse\n",
                check->connection_id);
#ifdef DEBUGBUILD
          if(check->recv_pipe->size > 0) {
            infof(data,
                  "BAD! Unconnected #%ld has a non-empty recv pipeline!\n",
                  check->connection_id);
          }
#endif
          continue;
        }
      }

      if((needle->handler->flags&PROTOPT_SSL) !=
         (check->handler->flags&PROTOPT_SSL))
        /* don't do mixed SSL and non-SSL connections */
        if(get_protocol_family(check->handler->protocol) !=
           needle->handler->protocol || !check->tls_upgraded)
          /* except protocols that have been upgraded via TLS */
          continue;

      if(needle->handler->flags&PROTOPT_SSL) {
        if((data->set.ssl.verifypeer != check->verifypeer) ||
           (data->set.ssl.verifyhost != check->verifyhost))
          continue;
      }

      if(needle->bits.proxy != check->bits.proxy)
        /* don't do mixed proxy and non-proxy connections */
        continue;

      if(needle->bits.proxy &&
         (needle->proxytype != check->proxytype ||
          needle->bits.httpproxy != check->bits.httpproxy ||
          needle->bits.tunnel_proxy != check->bits.tunnel_proxy ||
          !strcasecompare(needle->proxy.name, check->proxy.name) ||
          needle->port != check->port))
        /* don't mix connections that use different proxies */
        continue;

      if(needle->bits.conn_to_host != check->bits.conn_to_host)
        /* don't mix connections that use the "connect to host" feature and
         * connections that don't use this feature */
        continue;

      if(needle->bits.conn_to_port != check->bits.conn_to_port)
        /* don't mix connections that use the "connect to port" feature and
         * connections that don't use this feature */
        continue;

      if(!canPipeline && check->inuse)
        /* this request can't be pipelined but the checked connection is
           already in use so we skip it */
        continue;

      if(needle->localdev || needle->localport) {
        /* If we are bound to a specific local end (IP+port), we must not
           re-use a random other one, although if we didn't ask for a
           particular one we can reuse one that was bound.

           This comparison is a bit rough and too strict. Since the input
           parameters can be specified in numerous ways and still end up the
           same it would take a lot of processing to make it really accurate.
           Instead, this matching will assume that re-uses of bound connections
           will most likely also re-use the exact same binding parameters and
           missing out a few edge cases shouldn't hurt anyone very much.
        */
        if((check->localport != needle->localport) ||
           (check->localportrange != needle->localportrange) ||
           !check->localdev ||
           !needle->localdev ||
           strcmp(check->localdev, needle->localdev))
          continue;
      }

      if(!(needle->handler->flags & PROTOPT_CREDSPERREQUEST)) {
        /* This protocol requires credentials per connection,
           so verify that we're using the same name and password as well */
        if(strcmp(needle->user, check->user) ||
           strcmp(needle->passwd, check->passwd)) {
          /* one of them was different */
          continue;
        }
      }

      if(!needle->bits.httpproxy || (needle->handler->flags&PROTOPT_SSL) ||
         (needle->bits.httpproxy && needle->bits.tunnel_proxy)) {
        /* The requested connection does not use a HTTP proxy or it uses SSL or
           it is a non-SSL protocol tunneled over the same HTTP proxy name and
           port number */
        if((strcasecompare(needle->handler->scheme, check->handler->scheme) ||
            (get_protocol_family(check->handler->protocol) ==
             needle->handler->protocol && check->tls_upgraded)) &&
           (!needle->bits.conn_to_host || strcasecompare(
            needle->conn_to_host.name, check->conn_to_host.name)) &&
           (!needle->bits.conn_to_port ||
             needle->conn_to_port == check->conn_to_port) &&
           strcasecompare(needle->host.name, check->host.name) &&
           needle->remote_port == check->remote_port) {
          /* The schemes match or the the protocol family is the same and the
             previous connection was TLS upgraded, and the hostname and host
             port match */
          if(needle->handler->flags & PROTOPT_SSL) {
            /* This is a SSL connection so verify that we're using the same
               SSL options as well */
            if(!Curl_ssl_config_matches(&needle->ssl_config,
                                        &check->ssl_config)) {
              DEBUGF(infof(data,
                           "Connection #%ld has different SSL parameters, "
                           "can't reuse\n",
                           check->connection_id));
              continue;
            }
            else if(check->ssl[FIRSTSOCKET].state != ssl_connection_complete) {
              foundPendingCandidate = TRUE;
              DEBUGF(infof(data,
                           "Connection #%ld has not started SSL connect, "
                           "can't reuse\n",
                           check->connection_id));
              continue;
            }
          }
          match = TRUE;
        }
      }
      else {
        /* The requested connection is using the same HTTP proxy in normal
           mode (no tunneling) */
        match = TRUE;
      }

      if(match) {
#if defined(USE_NTLM)
        /* If we are looking for an HTTP+NTLM connection, check if this is
           already authenticating with the right credentials. If not, keep
           looking so that we can reuse NTLM connections if
           possible. (Especially we must not reuse the same connection if
           partway through a handshake!) */
        if(wantNTLMhttp) {
          if(strcmp(needle->user, check->user) ||
             strcmp(needle->passwd, check->passwd))
            continue;
        }
        else if(check->ntlm.state != NTLMSTATE_NONE) {
          /* Connection is using NTLM auth but we don't want NTLM */
          continue;
        }

        /* Same for Proxy NTLM authentication */
        if(wantProxyNTLMhttp) {
          /* Both check->proxyuser and check->proxypasswd can be NULL */
          if(!check->proxyuser || !check->proxypasswd)
            continue;

          if(strcmp(needle->proxyuser, check->proxyuser) ||
             strcmp(needle->proxypasswd, check->proxypasswd))
            continue;
        }
        else if(check->proxyntlm.state != NTLMSTATE_NONE) {
          /* Proxy connection is using NTLM auth but we don't want NTLM */
          continue;
        }

        if(wantNTLMhttp || wantProxyNTLMhttp) {
          /* Credentials are already checked, we can use this connection */
          chosen = check;

          if((wantNTLMhttp &&
             (check->ntlm.state != NTLMSTATE_NONE)) ||
              (wantProxyNTLMhttp &&
               (check->proxyntlm.state != NTLMSTATE_NONE))) {
            /* We must use this connection, no other */
            *force_reuse = TRUE;
            break;
          }

          /* Continue look up for a better connection */
          continue;
        }
#endif
        if(canPipeline) {
          /* We can pipeline if we want to. Let's continue looking for
             the optimal connection to use, i.e the shortest pipe that is not
             blacklisted. */

          if(pipeLen == 0) {
            /* We have the optimal connection. Let's stop looking. */
            chosen = check;
            break;
          }

          /* We can't use the connection if the pipe is full */
          if(max_pipe_len && (pipeLen >= max_pipe_len)) {
            infof(data, "Pipe is full, skip (%zu)\n", pipeLen);
            continue;
          }
#ifdef USE_NGHTTP2
          /* If multiplexed, make sure we don't go over concurrency limit */
          if(check->bits.multiplex) {
            /* Multiplexed connections can only be HTTP/2 for now */
            struct http_conn *httpc = &check->proto.httpc;
            if(pipeLen >= httpc->settings.max_concurrent_streams) {
              infof(data, "MAX_CONCURRENT_STREAMS reached, skip (%zu)\n",
                    pipeLen);
              continue;
            }
          }
#endif
          /* We can't use the connection if the pipe is penalized */
          if(Curl_pipeline_penalized(data, check)) {
            infof(data, "Penalized, skip\n");
            continue;
          }

          if(max_pipe_len) {
            if(pipeLen < best_pipe_len) {
              /* This connection has a shorter pipe so far. We'll pick this
                 and continue searching */
              chosen = check;
              best_pipe_len = pipeLen;
              continue;
            }
          }
          else {
            /* When not pipelining (== multiplexed), we have a match here! */
            chosen = check;
            infof(data, "Multiplexed connection found!\n");
            break;
          }
        }
        else {
          /* We have found a connection. Let's stop searching. */
          chosen = check;
          break;
        }
      }
    }
  }

  if(chosen) {
    *usethis = chosen;
    return TRUE; /* yes, we found one to use! */
  }

  if(foundPendingCandidate && data->set.pipewait) {
    infof(data,
          "Found pending candidate for reuse and CURLOPT_PIPEWAIT is set\n");
    *waitpipe = TRUE;
  }

  return FALSE; /* no matching connecting exists */
}