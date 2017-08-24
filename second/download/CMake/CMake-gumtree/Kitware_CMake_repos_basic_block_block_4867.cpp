h(data->mstate) {
    case CURLM_STATE_INIT:
      /* init this transfer. */
      result=Curl_pretransfer(data);

      if(!result) {
        /* after init, go CONNECT */
        multistate(data, CURLM_STATE_CONNECT);
        Curl_pgrsTime(data, TIMER_STARTOP);
        rc = CURLM_CALL_MULTI_PERFORM;
      }
      break;

    case CURLM_STATE_CONNECT_PEND:
      /* We will stay here until there is a connection available. Then
         we try again in the CURLM_STATE_CONNECT state. */
      break;

    case CURLM_STATE_CONNECT:
      /* Connect. We want to get a connection identifier filled in. */
      Curl_pgrsTime(data, TIMER_STARTSINGLE);
      result = Curl_connect(data, &data->easy_conn,
                            &async, &protocol_connect);
      if(CURLE_NO_CONNECTION_AVAILABLE == result) {
        /* There was no connection available. We will go to the pending
           state and wait for an available connection. */
        multistate(data, CURLM_STATE_CONNECT_PEND);

        /* add this handle to the list of connect-pending handles */
        Curl_llist_insert_next(&multi->pending, multi->pending.tail, data,
                               &data->connect_queue);
        result = CURLE_OK;
        break;
      }

      if(!result) {
        /* Add this handle to the send or pend pipeline */
        result = Curl_add_handle_to_pipeline(data, data->easy_conn);
        if(result)
          stream_error = TRUE;
        else {
          if(async)
            /* We're now waiting for an asynchronous name lookup */
            multistate(data, CURLM_STATE_WAITRESOLVE);
          else {
            /* after the connect has been sent off, go WAITCONNECT unless the
               protocol connect is already done and we can go directly to
               WAITDO or DO! */
            rc = CURLM_CALL_MULTI_PERFORM;

            if(protocol_connect)
              multistate(data, Curl_pipeline_wanted(multi, CURLPIPE_HTTP1)?
                         CURLM_STATE_WAITDO:CURLM_STATE_DO);
            else {
#ifndef CURL_DISABLE_HTTP
              if(data->easy_conn->tunnel_state[FIRSTSOCKET] == TUNNEL_CONNECT)
                multistate(data, CURLM_STATE_WAITPROXYCONNECT);
              else
#endif
                multistate(data, CURLM_STATE_WAITCONNECT);
            }
          }
        }
      }
      break;

    case CURLM_STATE_WAITRESOLVE:
      /* awaiting an asynch name resolve to complete */
    {
      struct Curl_dns_entry *dns = NULL;
      struct connectdata *conn = data->easy_conn;
      const char *hostname;

      if(conn->bits.httpproxy)
        hostname = conn->http_proxy.host.name;
      else if(conn->bits.conn_to_host)
        hostname = conn->conn_to_host.name;
      else
        hostname = conn->host.name;

      /* check if we have the name resolved by now */
      dns = Curl_fetch_addr(conn, hostname, (int)conn->port);

      if(dns) {
#ifdef CURLRES_ASYNCH
        conn->async.dns = dns;
        conn->async.done = TRUE;
#endif
        result = CURLE_OK;
        infof(data, "Hostname '%s' was found in DNS cache\n", hostname);
      }

      if(!dns)
        result = Curl_resolver_is_resolved(data->easy_conn, &dns);

      /* Update sockets here, because the socket(s) may have been
         closed and the application thus needs to be told, even if it
         is likely that the same socket(s) will again be used further
         down.  If the name has not yet been resolved, it is likely
         that new sockets have been opened in an attempt to contact
         another resolver. */
      singlesocket(multi, data);

      if(dns) {
        /* Perform the next step in the connection phase, and then move on
           to the WAITCONNECT state */
        result = Curl_async_resolved(data->easy_conn, &protocol_connect);

        if(result)
          /* if Curl_async_resolved() returns failure, the connection struct
             is already freed and gone */
          data->easy_conn = NULL;           /* no more connection */
        else {
          /* call again please so that we get the next socket setup */
          rc = CURLM_CALL_MULTI_PERFORM;
          if(protocol_connect)
            multistate(data, Curl_pipeline_wanted(multi, CURLPIPE_HTTP1)?
                       CURLM_STATE_WAITDO:CURLM_STATE_DO);
          else {
#ifndef CURL_DISABLE_HTTP
            if(data->easy_conn->tunnel_state[FIRSTSOCKET] == TUNNEL_CONNECT)
              multistate(data, CURLM_STATE_WAITPROXYCONNECT);
            else
#endif
              multistate(data, CURLM_STATE_WAITCONNECT);
          }
        }
      }

      if(result) {
        /* failure detected */
        stream_error = TRUE;
        break;
      }
    }
    break;

#ifndef CURL_DISABLE_HTTP
    case CURLM_STATE_WAITPROXYCONNECT:
      /* this is HTTP-specific, but sending CONNECT to a proxy is HTTP... */
      result = Curl_http_connect(data->easy_conn, &protocol_connect);

      if(data->easy_conn->bits.proxy_connect_closed) {
        rc = CURLM_CALL_MULTI_PERFORM;
        /* connect back to proxy again */
        result = CURLE_OK;
        multi_done(&data->easy_conn, CURLE_OK, FALSE);
        multistate(data, CURLM_STATE_CONNECT);
      }
      else if(!result) {
        if((data->easy_conn->http_proxy.proxytype != CURLPROXY_HTTPS ||
           data->easy_conn->bits.proxy_ssl_connected[FIRSTSOCKET]) &&
           (data->easy_conn->tunnel_state[FIRSTSOCKET] != TUNNEL_CONNECT)) {
          rc = CURLM_CALL_MULTI_PERFORM;
          /* initiate protocol connect phase */
          multistate(data, CURLM_STATE_SENDPROTOCONNECT);
        }
      }
      break;
#endif

    case CURLM_STATE_WAITCONNECT:
      /* awaiting a completion of an asynch TCP connect */
      result = Curl_is_connected(data->easy_conn, FIRSTSOCKET, &connected);
      if(connected && !result) {
#ifndef CURL_DISABLE_HTTP
        if((data->easy_conn->http_proxy.proxytype == CURLPROXY_HTTPS &&
            !data->easy_conn->bits.proxy_ssl_connected[FIRSTSOCKET]) ||
            (data->easy_conn->tunnel_state[FIRSTSOCKET] == TUNNEL_CONNECT)) {
          multistate(data, CURLM_STATE_WAITPROXYCONNECT);
          break;
        }
#endif
        rc = CURLM_CALL_MULTI_PERFORM;
        multistate(data, data->easy_conn->bits.tunnel_proxy?
                   CURLM_STATE_WAITPROXYCONNECT:
                   CURLM_STATE_SENDPROTOCONNECT);
      }
      else if(result) {
        /* failure detected */
        /* Just break, the cleaning up is handled all in one place */
        stream_error = TRUE;
        break;
      }
      break;

    case CURLM_STATE_SENDPROTOCONNECT:
      result = Curl_protocol_connect(data->easy_conn, &protocol_connect);
      if(!protocol_connect)
        /* switch to waiting state */
        multistate(data, CURLM_STATE_PROTOCONNECT);
      else if(!result) {
        /* protocol connect has completed, go WAITDO or DO */
        multistate(data, Curl_pipeline_wanted(multi, CURLPIPE_HTTP1)?
                   CURLM_STATE_WAITDO:CURLM_STATE_DO);
        rc = CURLM_CALL_MULTI_PERFORM;
      }
      else if(result) {
        /* failure detected */
        Curl_posttransfer(data);
        multi_done(&data->easy_conn, result, TRUE);
        stream_error = TRUE;
      }
      break;

    case CURLM_STATE_PROTOCONNECT:
      /* protocol-specific connect phase */
      result = Curl_protocol_connecting(data->easy_conn, &protocol_connect);
      if(!result && protocol_connect) {
        /* after the connect has completed, go WAITDO or DO */
        multistate(data, Curl_pipeline_wanted(multi, CURLPIPE_HTTP1)?
                   CURLM_STATE_WAITDO:CURLM_STATE_DO);
        rc = CURLM_CALL_MULTI_PERFORM;
      }
      else if(result) {
        /* failure detected */
        Curl_posttransfer(data);
        multi_done(&data->easy_conn, result, TRUE);
        stream_error = TRUE;
      }
      break;

    case CURLM_STATE_WAITDO:
      /* Wait for our turn to DO when we're pipelining requests */
      if(Curl_pipeline_checkget_write(data, data->easy_conn)) {
        /* Grabbed the channel */
        multistate(data, CURLM_STATE_DO);
        rc = CURLM_CALL_MULTI_PERFORM;
      }
      break;

    case CURLM_STATE_DO:
      if(data->set.connect_only) {
        /* keep connection open for application to use the socket */
        connkeep(data->easy_conn, "CONNECT_ONLY");
        multistate(data, CURLM_STATE_DONE);
        result = CURLE_OK;
        rc = CURLM_CALL_MULTI_PERFORM;
      }
      else {
        /* Perform the protocol's DO action */
        result = multi_do(&data->easy_conn, &dophase_done);

        /* When multi_do() returns failure, data->easy_conn might be NULL! */

        if(!result) {
          if(!dophase_done) {
            /* some steps needed for wildcard matching */
            if(data->set.wildcardmatch) {
              struct WildcardData *wc = &data->wildcard;
              if(wc->state == CURLWC_DONE || wc->state == CURLWC_SKIP) {
                /* skip some states if it is important */
                multi_done(&data->easy_conn, CURLE_OK, FALSE);
                multistate(data, CURLM_STATE_DONE);
                rc = CURLM_CALL_MULTI_PERFORM;
                break;
              }
            }
            /* DO was not completed in one function call, we must continue
               DOING... */
            multistate(data, CURLM_STATE_DOING);
            rc = CURLM_OK;
          }

          /* after DO, go DO_DONE... or DO_MORE */
          else if(data->easy_conn->bits.do_more) {
            /* we're supposed to do more, but we need to sit down, relax
               and wait a little while first */
            multistate(data, CURLM_STATE_DO_MORE);
            rc = CURLM_OK;
          }
          else {
            /* we're done with the DO, now DO_DONE */
            multistate(data, CURLM_STATE_DO_DONE);
            rc = CURLM_CALL_MULTI_PERFORM;
          }
        }
        else if((CURLE_SEND_ERROR == result) &&
                data->easy_conn->bits.reuse) {
          /*
           * In this situation, a connection that we were trying to use
           * may have unexpectedly died.  If possible, send the connection
           * back to the CONNECT phase so we can try again.
           */
          char *newurl = NULL;
          followtype follow=FOLLOW_NONE;
          CURLcode drc;
          bool retry = FALSE;

          drc = Curl_retry_request(data->easy_conn, &newurl);
          if(drc) {
            /* a failure here pretty much implies an out of memory */
            result = drc;
            stream_error = TRUE;
          }
          else
            retry = (newurl)?TRUE:FALSE;

          Curl_posttransfer(data);
          drc = multi_done(&data->easy_conn, result, FALSE);

          /* When set to retry the connection, we must to go back to
           * the CONNECT state */
          if(retry) {
            if(!drc || (drc == CURLE_SEND_ERROR)) {
              follow = FOLLOW_RETRY;
              drc = Curl_follow(data, newurl, follow);
              if(!drc) {
                multistate(data, CURLM_STATE_CONNECT);
                rc = CURLM_CALL_MULTI_PERFORM;
                result = CURLE_OK;
              }
              else {
                /* Follow failed */
                result = drc;
              }
            }
            else {
              /* done didn't return OK or SEND_ERROR */
              result = drc;
            }
          }
          else {
            /* Have error handler disconnect conn if we can't retry */
            stream_error = TRUE;
          }
          free(newurl);
        }
        else {
          /* failure detected */
          Curl_posttransfer(data);
          if(data->easy_conn)
            multi_done(&data->easy_conn, result, FALSE);
          stream_error = TRUE;
        }
      }
      break;

    case CURLM_STATE_DOING:
      /* we continue DOING until the DO phase is complete */
      result = Curl_protocol_doing(data->easy_conn,
                                   &dophase_done);
      if(!result) {
        if(dophase_done) {
          /* after DO, go DO_DONE or DO_MORE */
          multistate(data, data->easy_conn->bits.do_more?
                     CURLM_STATE_DO_MORE:
                     CURLM_STATE_DO_DONE);
          rc = CURLM_CALL_MULTI_PERFORM;
        } /* dophase_done */
      }
      else {
        /* failure detected */
        Curl_posttransfer(data);
        multi_done(&data->easy_conn, result, FALSE);
        stream_error = TRUE;
      }
      break;

    case CURLM_STATE_DO_MORE:
      /*
       * When we are connected, DO MORE and then go DO_DONE
       */
      result = multi_do_more(data->easy_conn, &control);

      /* No need to remove this handle from the send pipeline here since that
         is done in multi_done() */
      if(!result) {
        if(control) {
          /* if positive, advance to DO_DONE
             if negative, go back to DOING */
          multistate(data, control==1?
                     CURLM_STATE_DO_DONE:
                     CURLM_STATE_DOING);
          rc = CURLM_CALL_MULTI_PERFORM;
        }
        else
          /* stay in DO_MORE */
          rc = CURLM_OK;
      }
      else {
        /* failure detected */
        Curl_posttransfer(data);
        multi_done(&data->easy_conn, result, FALSE);
        stream_error = TRUE;
      }
      break;

    case CURLM_STATE_DO_DONE:
      /* Move ourselves from the send to recv pipeline */
      Curl_move_handle_from_send_to_recv_pipe(data, data->easy_conn);
      /* Check if we can move pending requests to send pipe */
      Curl_multi_process_pending_handles(multi);

      /* Only perform the transfer if there's a good socket to work with.
         Having both BAD is a signal to skip immediately to DONE */
      if((data->easy_conn->sockfd != CURL_SOCKET_BAD) ||
         (data->easy_conn->writesockfd != CURL_SOCKET_BAD))
        multistate(data, CURLM_STATE_WAITPERFORM);
      else
        multistate(data, CURLM_STATE_DONE);
      rc = CURLM_CALL_MULTI_PERFORM;
      break;

    case CURLM_STATE_WAITPERFORM:
      /* Wait for our turn to PERFORM */
      if(Curl_pipeline_checkget_read(data, data->easy_conn)) {
        /* Grabbed the channel */
        multistate(data, CURLM_STATE_PERFORM);
        rc = CURLM_CALL_MULTI_PERFORM;
      }
      break;

    case CURLM_STATE_TOOFAST: /* limit-rate exceeded in either direction */
      /* if both rates are within spec, resume transfer */
      if(Curl_pgrsUpdate(data->easy_conn))
        result = CURLE_ABORTED_BY_CALLBACK;
      else
        result = Curl_speedcheck(data, now);

      if(!result) {
        send_timeout_ms = 0;
        if(data->set.max_send_speed > 0)
          send_timeout_ms = Curl_pgrsLimitWaitTime(data->progress.uploaded,
                                data->progress.ul_limit_size,
                                data->set.max_send_speed,
                                data->progress.ul_limit_start,
                                now);

        recv_timeout_ms = 0;
        if(data->set.max_recv_speed > 0)
          recv_timeout_ms = Curl_pgrsLimitWaitTime(data->progress.downloaded,
                                data->progress.dl_limit_size,
                                data->set.max_recv_speed,
                                data->progress.dl_limit_start,
                                now);

        if(send_timeout_ms <= 0 && recv_timeout_ms <= 0)
          multistate(data, CURLM_STATE_PERFORM);
        else if(send_timeout_ms >= recv_timeout_ms)
          Curl_expire(data, send_timeout_ms, EXPIRE_TOOFAST);
        else
          Curl_expire(data, recv_timeout_ms, EXPIRE_TOOFAST);
      }
      break;

    case CURLM_STATE_PERFORM:
    {
      char *newurl = NULL;
      bool retry = FALSE;
      bool comeback = FALSE;

      /* check if over send speed */
      send_timeout_ms = 0;
      if(data->set.max_send_speed > 0)
        send_timeout_ms = Curl_pgrsLimitWaitTime(data->progress.uploaded,
                                                 data->progress.ul_limit_size,
                                                 data->set.max_send_speed,
                                                 data->progress.ul_limit_start,
                                                 now);

      /* check if over recv speed */
      recv_timeout_ms = 0;
      if(data->set.max_recv_speed > 0)
        recv_timeout_ms = Curl_pgrsLimitWaitTime(data->progress.downloaded,
                                                 data->progress.dl_limit_size,
                                                 data->set.max_recv_speed,
                                                 data->progress.dl_limit_start,
                                                 now);

      if(send_timeout_ms > 0 || recv_timeout_ms > 0) {
        multistate(data, CURLM_STATE_TOOFAST);
        if(send_timeout_ms >= recv_timeout_ms)
          Curl_expire(data, send_timeout_ms, EXPIRE_TOOFAST);
        else
          Curl_expire(data, recv_timeout_ms, EXPIRE_TOOFAST);
        break;
      }

      /* read/write data if it is ready to do so */
      result = Curl_readwrite(data->easy_conn, data, &done, &comeback);

      k = &data->req;

      if(!(k->keepon & KEEP_RECV))
        /* We're done receiving */
        Curl_pipeline_leave_read(data->easy_conn);

      if(!(k->keepon & KEEP_SEND))
        /* We're done sending */
        Curl_pipeline_leave_write(data->easy_conn);

      if(done || (result == CURLE_RECV_ERROR)) {
        /* If CURLE_RECV_ERROR happens early enough, we assume it was a race
         * condition and the server closed the re-used connection exactly when
         * we wanted to use it, so figure out if that is indeed the case.
         */
        CURLcode ret = Curl_retry_request(data->easy_conn, &newurl);
        if(!ret)
          retry = (newurl)?TRUE:FALSE;

        if(retry) {
          /* if we are to retry, set the result to OK and consider the
             request as done */
          result = CURLE_OK;
          done = TRUE;
        }
      }

      if(result) {
        /*
         * The transfer phase returned error, we mark the connection to get
         * closed to prevent being re-used. This is because we can't possibly
         * know if the connection is in a good shape or not now.  Unless it is
         * a protocol which uses two "channels" like FTP, as then the error
         * happened in the data connection.
         */

        if(!(data->easy_conn->handler->flags & PROTOPT_DUAL) &&
           result != CURLE_HTTP2_STREAM)
          streamclose(data->easy_conn, "Transfer returned error");

        Curl_posttransfer(data);
        multi_done(&data->easy_conn, result, TRUE);
      }
      else if(done) {
        followtype follow=FOLLOW_NONE;

        /* call this even if the readwrite function returned error */
        Curl_posttransfer(data);

        /* we're no longer receiving */
        Curl_removeHandleFromPipeline(data, &data->easy_conn->recv_pipe);

        /* expire the new receiving pipeline head */
        if(data->easy_conn->recv_pipe.head)
          Curl_expire(data->easy_conn->recv_pipe.head->ptr, 0, EXPIRE_RUN_NOW);

        /* Check if we can move pending requests to send pipe */
        Curl_multi_process_pending_handles(multi);

        /* When we follow redirects or is set to retry the connection, we must
           to go back to the CONNECT state */
        if(data->req.newurl || retry) {
          if(!retry) {
            /* if the URL is a follow-location and not just a retried request
               then figure out the URL here */
            free(newurl);
            newurl = data->req.newurl;
            data->req.newurl = NULL;
            follow = FOLLOW_REDIR;
          }
          else
            follow = FOLLOW_RETRY;
          result = multi_done(&data->easy_conn, CURLE_OK, FALSE);
          if(!result) {
            result = Curl_follow(data, newurl, follow);
            if(!result) {
              multistate(data, CURLM_STATE_CONNECT);
              rc = CURLM_CALL_MULTI_PERFORM;
            }
          }
        }
        else {
          /* after the transfer is done, go DONE */

          /* but first check to see if we got a location info even though we're
             not following redirects */
          if(data->req.location) {
            free(newurl);
            newurl = data->req.location;
            data->req.location = NULL;
            result = Curl_follow(data, newurl, FOLLOW_FAKE);
            if(result)
              stream_error = TRUE;
          }

          multistate(data, CURLM_STATE_DONE);
          rc = CURLM_CALL_MULTI_PERFORM;
        }
      }
      else if(comeback)
        rc = CURLM_CALL_MULTI_PERFORM;

      free(newurl);
      break;
    }

    case CURLM_STATE_DONE:
      /* this state is highly transient, so run another loop after this */
      rc = CURLM_CALL_MULTI_PERFORM;

      if(data->easy_conn) {
        CURLcode res;

        /* Remove ourselves from the receive pipeline, if we are there. */
        Curl_removeHandleFromPipeline(data, &data->easy_conn->recv_pipe);
        /* Check if we can move pending requests to send pipe */
        Curl_multi_process_pending_handles(multi);

        /* post-transfer command */
        res = multi_done(&data->easy_conn, result, FALSE);

        /* allow a previously set error code take precedence */
        if(!result)
          result = res;

        /*
         * If there are other handles on the pipeline, multi_done won't set
         * easy_conn to NULL.  In such a case, curl_multi_remove_handle() can
         * access free'd data, if the connection is free'd and the handle
         * removed before we perform the processing in CURLM_STATE_COMPLETED
         */
        if(data->easy_conn)
          data->easy_conn = NULL;
      }

      if(data->set.wildcardmatch) {
        if(data->wildcard.state != CURLWC_DONE) {
          /* if a wildcard is set and we are not ending -> lets start again
             with CURLM_STATE_INIT */
          multistate(data, CURLM_STATE_INIT);
          break;
        }
      }

      /* after we have DONE what we're supposed to do, go COMPLETED, and
         it doesn't matter what the multi_done() returned! */
      multistate(data, CURLM_STATE_COMPLETED);
      break;

    case CURLM_STATE_COMPLETED:
      /* this is a completed transfer, it is likely to still be connected */

      /* This node should be delinked from the list now and we should post
         an information message that we are complete. */

      /* Important: reset the conn pointer so that we don't point to memory
         that could be freed anytime */
      data->easy_conn = NULL;

      Curl_expire_clear(data); /* stop all timers */
      break;

    case CURLM_STATE_MSGSENT:
      data->result = result;
      return CURLM_OK; /* do nothing */

    default:
      return CURLM_INTERNAL_ERROR;
    }