static CURLMcode multi_runsingle(struct Curl_multi *multi,
                                 struct Curl_one_easy *easy)
{
  struct Curl_message *msg = NULL;
  bool connected;
  bool async;
  bool protocol_connect = FALSE;
  bool dophase_done;
  bool done;
  CURLMcode result = CURLM_OK;
  struct SingleRequest *k;

  if(!GOOD_EASY_HANDLE(easy->easy_handle))
    return CURLM_BAD_EASY_HANDLE;

  do {
    /* this is a do-while loop just to allow a break to skip to the end
       of it */
    bool disconnect_conn = FALSE;

    /* Handle the case when the pipe breaks, i.e., the connection
       we're using gets cleaned up and we're left with nothing. */
    if(easy->easy_handle->state.pipe_broke) {
      infof(easy->easy_handle, "Pipe broke: handle 0x%x, url = %s\n",
            easy, easy->easy_handle->state.path);

      if(easy->state != CURLM_STATE_COMPLETED) {
        /* Head back to the CONNECT state */
        multistate(easy, CURLM_STATE_CONNECT);
        result = CURLM_CALL_MULTI_PERFORM;
        easy->result = CURLE_OK;
      }

      easy->easy_handle->state.pipe_broke = FALSE;
      easy->easy_conn = NULL;
      break;
    }

    if(easy->state > CURLM_STATE_CONNECT &&
       easy->state < CURLM_STATE_COMPLETED)
      /* Make sure we set the connection's current owner */
      easy->easy_conn->data = easy->easy_handle;

    switch(easy->state) {
    case CURLM_STATE_INIT:
      /* init this transfer. */
      easy->result=Curl_pretransfer(easy->easy_handle);

      if(CURLE_OK == easy->result) {
        /* after init, go CONNECT */
        multistate(easy, CURLM_STATE_CONNECT);
        result = CURLM_CALL_MULTI_PERFORM;

        easy->easy_handle->state.used_interface = Curl_if_multi;
      }
      break;

    case CURLM_STATE_CONNECT:
      /* Connect. We get a connection identifier filled in. */
      Curl_pgrsTime(easy->easy_handle, TIMER_STARTSINGLE);
      easy->result = Curl_connect(easy->easy_handle, &easy->easy_conn,
                                  &async, &protocol_connect);

      if(CURLE_OK == easy->result) {
        /* Add this handle to the send or pend pipeline */
        easy->result = addHandleToSendOrPendPipeline(easy->easy_handle,
                                                     easy->easy_conn);
        if(CURLE_OK == easy->result) {
          if(async)
            /* We're now waiting for an asynchronous name lookup */
            multistate(easy, CURLM_STATE_WAITRESOLVE);
          else {
            /* after the connect has been sent off, go WAITCONNECT unless the
               protocol connect is already done and we can go directly to
               WAITDO! */
            result = CURLM_CALL_MULTI_PERFORM;

            if(protocol_connect)
              multistate(easy, CURLM_STATE_WAITDO);
            else {
#ifndef CURL_DISABLE_HTTP
              if(easy->easy_conn->bits.tunnel_connecting)
                multistate(easy, CURLM_STATE_WAITPROXYCONNECT);
              else
#endif
                multistate(easy, CURLM_STATE_WAITCONNECT);
            }
          }
        }
      }
      break;

    case CURLM_STATE_WAITRESOLVE:
      /* awaiting an asynch name resolve to complete */
    {
      struct Curl_dns_entry *dns = NULL;

      /* check if we have the name resolved by now */
      easy->result = Curl_is_resolved(easy->easy_conn, &dns);

      if(dns) {
        /* Perform the next step in the connection phase, and then move on
           to the WAITCONNECT state */
        easy->result = Curl_async_resolved(easy->easy_conn,
                                           &protocol_connect);

        if(CURLE_OK != easy->result)
          /* if Curl_async_resolved() returns failure, the connection struct
             is already freed and gone */
          easy->easy_conn = NULL;           /* no more connection */
        else {
          /* call again please so that we get the next socket setup */
          result = CURLM_CALL_MULTI_PERFORM;
          if(protocol_connect)
            multistate(easy, CURLM_STATE_WAITDO);
          else {
#ifndef CURL_DISABLE_HTTP
            if(easy->easy_conn->bits.tunnel_connecting)
              multistate(easy, CURLM_STATE_WAITPROXYCONNECT);
            else
#endif
              multistate(easy, CURLM_STATE_WAITCONNECT);
          }
        }
      }

      if(CURLE_OK != easy->result) {
        /* failure detected */
        disconnect_conn = TRUE;
        break;
      }
    }
    break;

#ifndef CURL_DISABLE_HTTP
    case CURLM_STATE_WAITPROXYCONNECT:
      /* this is HTTP-specific, but sending CONNECT to a proxy is HTTP... */
      easy->result = Curl_http_connect(easy->easy_conn, &protocol_connect);

      if(CURLE_OK == easy->result) {
        if(!easy->easy_conn->bits.tunnel_connecting)
          multistate(easy, CURLM_STATE_WAITCONNECT);
      }
      break;
#endif

    case CURLM_STATE_WAITCONNECT:
      /* awaiting a completion of an asynch connect */
      easy->result = Curl_is_connected(easy->easy_conn,
                                       FIRSTSOCKET,
                                       &connected);
      if(connected)
        easy->result = Curl_protocol_connect(easy->easy_conn,
                                             &protocol_connect);

      if(CURLE_OK != easy->result) {
        /* failure detected */
        /* Just break, the cleaning up is handled all in one place */
        disconnect_conn = TRUE;
        break;
      }

      if(connected) {
        if(!protocol_connect) {
          /* We have a TCP connection, but 'protocol_connect' may be false
             and then we continue to 'STATE_PROTOCONNECT'. If protocol
             connect is TRUE, we move on to STATE_DO.
             BUT if we are using a proxy we must change to WAITPROXYCONNECT
             */
#ifndef CURL_DISABLE_HTTP
          if(easy->easy_conn->bits.tunnel_connecting)
            multistate(easy, CURLM_STATE_WAITPROXYCONNECT);
          else
#endif
            multistate(easy, CURLM_STATE_PROTOCONNECT);
        }
        else {
          /* after the connect has completed, go WAITDO */
          multistate(easy, CURLM_STATE_WAITDO);

          result = CURLM_CALL_MULTI_PERFORM;
        }
      }
      break;

    case CURLM_STATE_PROTOCONNECT:
      /* protocol-specific connect phase */
      easy->result = Curl_protocol_connecting(easy->easy_conn,
                                              &protocol_connect);
      if((easy->result == CURLE_OK) && protocol_connect) {
        /* after the connect has completed, go WAITDO */
        multistate(easy, CURLM_STATE_WAITDO);
        result = CURLM_CALL_MULTI_PERFORM;
      }
      else if(easy->result) {
        /* failure detected */
        Curl_posttransfer(easy->easy_handle);
        Curl_done(&easy->easy_conn, easy->result, FALSE);
        disconnect_conn = TRUE;
      }
      break;

    case CURLM_STATE_WAITDO:
      /* Wait for our turn to DO when we're pipelining requests */
#ifdef CURLDEBUG
      infof(easy->easy_handle, "Conn %d send pipe %d inuse %d athead %d\n",
            easy->easy_conn->connectindex,
            easy->easy_conn->send_pipe->size,
            easy->easy_conn->writechannel_inuse,
            isHandleAtHead(easy->easy_handle,
                           easy->easy_conn->send_pipe));
#endif
      if(!easy->easy_conn->writechannel_inuse &&
         isHandleAtHead(easy->easy_handle,
                        easy->easy_conn->send_pipe)) {
        /* Grab the channel */
        easy->easy_conn->writechannel_inuse = TRUE;
        multistate(easy, CURLM_STATE_DO);
        result = CURLM_CALL_MULTI_PERFORM;
      }
      break;

    case CURLM_STATE_DO:
      if(easy->easy_handle->set.connect_only) {
        /* keep connection open for application to use the socket */
        easy->easy_conn->bits.close = FALSE;
        multistate(easy, CURLM_STATE_DONE);
        easy->result = CURLE_OK;
        result = CURLM_OK;
      }
      else {
        /* Perform the protocol's DO action */
        easy->result = Curl_do(&easy->easy_conn,
                               &dophase_done);

        if(CURLE_OK == easy->result) {

          if(!dophase_done) {
            /* DO was not completed in one function call, we must continue
               DOING... */
            multistate(easy, CURLM_STATE_DOING);
            result = CURLM_OK;
          }

          /* after DO, go DO_DONE... or DO_MORE */
          else if(easy->easy_conn->bits.do_more) {
            /* we're supposed to do more, but we need to sit down, relax
               and wait a little while first */
            multistate(easy, CURLM_STATE_DO_MORE);
            result = CURLM_OK;
          }
          else {
            /* we're done with the DO, now DO_DONE */
            multistate(easy, CURLM_STATE_DO_DONE);
            result = CURLM_CALL_MULTI_PERFORM;
          }
        }
        else {
          /* failure detected */
          Curl_posttransfer(easy->easy_handle);
          Curl_done(&easy->easy_conn, easy->result, FALSE);
          disconnect_conn = TRUE;
        }
      }
      break;

    case CURLM_STATE_DOING:
      /* we continue DOING until the DO phase is complete */
      easy->result = Curl_protocol_doing(easy->easy_conn,
                                         &dophase_done);
      if(CURLE_OK == easy->result) {
        if(dophase_done) {
          /* after DO, go PERFORM... or DO_MORE */
          if(easy->easy_conn->bits.do_more) {
            /* we're supposed to do more, but we need to sit down, relax
               and wait a little while first */
            multistate(easy, CURLM_STATE_DO_MORE);
            result = CURLM_OK;
          }
          else {
            /* we're done with the DO, now DO_DONE */
            multistate(easy, CURLM_STATE_DO_DONE);
            result = CURLM_CALL_MULTI_PERFORM;
          }
        } /* dophase_done */
      }
      else {
        /* failure detected */
        Curl_posttransfer(easy->easy_handle);
        Curl_done(&easy->easy_conn, easy->result, FALSE);
        disconnect_conn = TRUE;
      }
      break;

    case CURLM_STATE_DO_MORE:
      /* Ready to do more? */
      easy->result = Curl_is_connected(easy->easy_conn,
                                       SECONDARYSOCKET,
                                       &connected);
      if(connected) {
        /*
         * When we are connected, DO MORE and then go DO_DONE
         */
        easy->result = Curl_do_more(easy->easy_conn);

        /* No need to remove ourselves from the send pipeline here since that
           is done for us in Curl_done() */

        if(CURLE_OK == easy->result) {
          multistate(easy, CURLM_STATE_DO_DONE);
          result = CURLM_CALL_MULTI_PERFORM;
        }
        else {
          /* failure detected */
          Curl_posttransfer(easy->easy_handle);
          Curl_done(&easy->easy_conn, easy->result, FALSE);
          disconnect_conn = TRUE;
        }
      }
      break;

    case CURLM_STATE_DO_DONE:
      /* Move ourselves from the send to recv pipeline */
      moveHandleFromSendToRecvPipeline(easy->easy_handle, easy->easy_conn);
      /* Check if we can move pending requests to send pipe */
      checkPendPipeline(easy->easy_conn);
      multistate(easy, CURLM_STATE_WAITPERFORM);
      result = CURLM_CALL_MULTI_PERFORM;
      break;

    case CURLM_STATE_WAITPERFORM:
#ifdef CURLDEBUG
      infof(easy->easy_handle, "Conn %d recv pipe %d inuse %d athead %d\n",
            easy->easy_conn->connectindex,
            easy->easy_conn->recv_pipe->size,
            easy->easy_conn->readchannel_inuse,
            isHandleAtHead(easy->easy_handle,
                           easy->easy_conn->recv_pipe));
#endif
      /* Wait for our turn to PERFORM */
      if(!easy->easy_conn->readchannel_inuse &&
         isHandleAtHead(easy->easy_handle,
                        easy->easy_conn->recv_pipe)) {
        /* Grab the channel */
        easy->easy_conn->readchannel_inuse = TRUE;
        multistate(easy, CURLM_STATE_PERFORM);
        result = CURLM_CALL_MULTI_PERFORM;
      }
      break;

    case CURLM_STATE_TOOFAST: /* limit-rate exceeded in either direction */
      /* if both rates are within spec, resume transfer */
      Curl_pgrsUpdate(easy->easy_conn);
      if( ( ( easy->easy_handle->set.max_send_speed == 0 ) ||
             ( easy->easy_handle->progress.ulspeed <
               easy->easy_handle->set.max_send_speed ) )  &&
           ( ( easy->easy_handle->set.max_recv_speed == 0 ) ||
             ( easy->easy_handle->progress.dlspeed <
               easy->easy_handle->set.max_recv_speed ) )
        )
      multistate(easy, CURLM_STATE_PERFORM);
      break;

    case CURLM_STATE_PERFORM:
      /* check if over speed */
      if( (  ( easy->easy_handle->set.max_send_speed > 0 ) &&
              ( easy->easy_handle->progress.ulspeed >
                easy->easy_handle->set.max_send_speed ) )  ||
           (  ( easy->easy_handle->set.max_recv_speed > 0 ) &&
              ( easy->easy_handle->progress.dlspeed >
                easy->easy_handle->set.max_recv_speed ) )
        ) {
        /* Transfer is over the speed limit. Change state.  TODO: Call
         * Curl_expire() with the time left until we're targeted to be below
         * the speed limit again. */
        multistate(easy, CURLM_STATE_TOOFAST );
        break;
      }

      /* read/write data if it is ready to do so */
      easy->result = Curl_readwrite(easy->easy_conn, &done);

      k = &easy->easy_handle->req;

      if(!(k->keepon & KEEP_READ)) {
        /* We're done reading */
        easy->easy_conn->readchannel_inuse = FALSE;
      }

      if(!(k->keepon & KEEP_WRITE)) {
        /* We're done writing */
        easy->easy_conn->writechannel_inuse = FALSE;
      }

      if(easy->result)  {
        /* The transfer phase returned error, we mark the connection to get
         * closed to prevent being re-used. This is because we can't
         * possibly know if the connection is in a good shape or not now. */
        easy->easy_conn->bits.close = TRUE;
        Curl_removeHandleFromPipeline(easy->easy_handle,
                                      easy->easy_conn->recv_pipe);

        if(CURL_SOCKET_BAD != easy->easy_conn->sock[SECONDARYSOCKET]) {
          /* if we failed anywhere, we must clean up the secondary socket if
             it was used */
          sclose(easy->easy_conn->sock[SECONDARYSOCKET]);
          easy->easy_conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD;
        }
        Curl_posttransfer(easy->easy_handle);
        Curl_done(&easy->easy_conn, easy->result, FALSE);
      }
      else if(TRUE == done) {
        char *newurl;
        bool retry = Curl_retry_request(easy->easy_conn, &newurl);

        /* call this even if the readwrite function returned error */
        Curl_posttransfer(easy->easy_handle);

        /* When we follow redirects, must to go back to the CONNECT state */
        if(easy->easy_handle->req.newurl || retry) {
          Curl_removeHandleFromPipeline(easy->easy_handle,
                                        easy->easy_conn->recv_pipe);
          /* Check if we can move pending requests to send pipe */
          checkPendPipeline(easy->easy_conn);

          if(!retry) {
            /* if the URL is a follow-location and not just a retried request
               then figure out the URL here */
            newurl = easy->easy_handle->req.newurl;
            easy->easy_handle->req.newurl = NULL;
          }
          easy->result = Curl_done(&easy->easy_conn, CURLE_OK, FALSE);
          if(easy->result == CURLE_OK)
            easy->result = Curl_follow(easy->easy_handle, newurl, retry);
          if(CURLE_OK == easy->result) {
            multistate(easy, CURLM_STATE_CONNECT);
            result = CURLM_CALL_MULTI_PERFORM;
          }
          else
            /* Since we "took it", we are in charge of freeing this on
               failure */
            free(newurl);
        }
        else {
          /* after the transfer is done, go DONE */
          multistate(easy, CURLM_STATE_DONE);
          result = CURLM_CALL_MULTI_PERFORM;
        }
      }

      break;

    case CURLM_STATE_DONE:
      /* Remove ourselves from the receive pipeline */
      Curl_removeHandleFromPipeline(easy->easy_handle,
                                    easy->easy_conn->recv_pipe);
      /* Check if we can move pending requests to send pipe */
      checkPendPipeline(easy->easy_conn);

      if(easy->easy_conn->bits.stream_was_rewound) {
          /* This request read past its response boundary so we quickly
             let the other requests consume those bytes since there is no
             guarantee that the socket will become active again */
          result = CURLM_CALL_MULTI_PERFORM;
      }

      /* post-transfer command */
      easy->result = Curl_done(&easy->easy_conn, CURLE_OK, FALSE);

      /* after we have DONE what we're supposed to do, go COMPLETED, and
         it doesn't matter what the Curl_done() returned! */
      multistate(easy, CURLM_STATE_COMPLETED);

      break;

    case CURLM_STATE_COMPLETED:
      /* this is a completed transfer, it is likely to still be connected */

      /* This node should be delinked from the list now and we should post
         an information message that we are complete. */

      /* Important: reset the conn pointer so that we don't point to memory
         that could be freed anytime */
      easy->easy_conn = NULL;
      break;

    default:
      return CURLM_INTERNAL_ERROR;
    }

    if(CURLM_STATE_COMPLETED != easy->state) {
      if(CURLE_OK != easy->result) {
        /*
         * If an error was returned, and we aren't in completed state now,
         * then we go to completed and consider this transfer aborted.
         */

        /* NOTE: no attempt to disconnect connections must be made
           in the case blocks above - cleanup happens only here */

        easy->easy_handle->state.pipe_broke = FALSE;

        if(easy->easy_conn) {
          /* if this has a connection, unsubscribe from the pipelines */
          easy->easy_conn->writechannel_inuse = FALSE;
          easy->easy_conn->readchannel_inuse = FALSE;
          Curl_removeHandleFromPipeline(easy->easy_handle,
                                        easy->easy_conn->send_pipe);
          Curl_removeHandleFromPipeline(easy->easy_handle,
                                        easy->easy_conn->recv_pipe);
          /* Check if we can move pending requests to send pipe */
          checkPendPipeline(easy->easy_conn);
        }

        if(disconnect_conn) {
          Curl_disconnect(easy->easy_conn); /* disconnect properly */

          /* This is where we make sure that the easy_conn pointer is reset.
             We don't have to do this in every case block above where a
             failure is detected */
          easy->easy_conn = NULL;
        }

        multistate(easy, CURLM_STATE_COMPLETED);
      }
    }
  } while(0);
  if((CURLM_STATE_COMPLETED == easy->state) && !easy->msg) {
    if(easy->easy_handle->dns.hostcachetype == HCACHE_MULTI) {
      /* clear out the usage of the shared DNS cache */
      easy->easy_handle->dns.hostcache = NULL;
      easy->easy_handle->dns.hostcachetype = HCACHE_NONE;
    }

    /* now add a node to the Curl_message linked list with this info */
    msg = (struct Curl_message *)malloc(sizeof(struct Curl_message));

    if(!msg)
      return CURLM_OUT_OF_MEMORY;

    msg->extmsg.msg = CURLMSG_DONE;
    msg->extmsg.easy_handle = easy->easy_handle;
    msg->extmsg.data.result = easy->result;
    msg->next = NULL;

    easy->msg = msg;
    easy->msg_num = 1; /* there is one unread message here */

    multi->num_msgs++; /* increase message counter */
  }

  if(CURLM_CALL_MULTI_PERFORM == result)
    /* Set the timeout for this handle to expire really soon so that it will
       be taken care of even when this handle is added in the midst of
       operation when only the curl_multi_socket() API is used. During that
       flow, only sockets that time-out or have actions will be dealt
       with. Since this handle has no action yet, we make sure it times out to
       get things to happen. Also, this makes it less important for callers of
       the curl_multi_* functions to bother about the CURLM_CALL_MULTI_PERFORM
       return code, as long as they deal with the timeouts properly. */
    Curl_expire(easy->easy_handle, 10);

  return result;
}