CURLMcode curl_multi_perform(CURLM *multi_handle, int *running_handles)
{
  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
  struct Curl_one_easy *easy;
  bool done;
  CURLMcode result=CURLM_OK;
  struct Curl_message *msg = NULL;
  bool connected;
  bool async;
  bool protocol_connect;
  bool dophase_done;

  *running_handles = 0; /* bump this once for every living handle */

  if(!GOOD_MULTI_HANDLE(multi))
    return CURLM_BAD_HANDLE;

  easy=multi->easy.next;
  while(easy) {
    do {
      if (CURLM_STATE_WAITCONNECT <= easy->state &&
          easy->state <= CURLM_STATE_DO &&
          easy->easy_handle->change.url_changed) {
        char *gotourl;
        Curl_posttransfer(easy->easy_handle);

        easy->result = Curl_done(&easy->easy_conn, CURLE_OK);
        if(CURLE_OK == easy->result) {
          gotourl = strdup(easy->easy_handle->change.url);
          if(gotourl) {
            easy->easy_handle->change.url_changed = FALSE;
            easy->result = Curl_follow(easy->easy_handle, gotourl, FALSE);
            if(CURLE_OK == easy->result)
              multistate(easy, CURLM_STATE_CONNECT);
            else
              free(gotourl);
          }
          else {
            easy->result = CURLE_OUT_OF_MEMORY;
            multistate(easy, CURLM_STATE_COMPLETED);
            break;
          }
        }
      }

      easy->easy_handle->change.url_changed = FALSE;

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
          if(async)
            /* We're now waiting for an asynchronous name lookup */
            multistate(easy, CURLM_STATE_WAITRESOLVE);
          else {
            /* after the connect has been sent off, go WAITCONNECT unless the
               protocol connect is already done and we can go directly to
               DO! */
            result = CURLM_CALL_MULTI_PERFORM;

            if(protocol_connect)
              multistate(easy, CURLM_STATE_DO);
            else
              multistate(easy, CURLM_STATE_WAITCONNECT);
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
            /* FIX: what if protocol_connect is TRUE here?! */
            multistate(easy, CURLM_STATE_WAITCONNECT);
          }
        }

        if(CURLE_OK != easy->result) {
          /* failure detected */
          Curl_disconnect(easy->easy_conn); /* disconnect properly */
          easy->easy_conn = NULL;           /* no more connection */
          break;
        }
      }
      break;

      case CURLM_STATE_WAITCONNECT:
        /* awaiting a completion of an asynch connect */
        easy->result = Curl_is_connected(easy->easy_conn, FIRSTSOCKET,
                                         &connected);
        if(connected)
          easy->result = Curl_protocol_connect(easy->easy_conn,
                                               &protocol_connect);

        if(CURLE_OK != easy->result) {
          /* failure detected */
          Curl_disconnect(easy->easy_conn); /* close the connection */
          easy->easy_conn = NULL;           /* no more connection */
          break;
        }

        if(connected) {
          if(!protocol_connect) {
            /* We have a TCP connection, but 'protocol_connect' may be false
               and then we continue to 'STATE_PROTOCONNECT'. If protocol
               connect is TRUE, we move on to STATE_DO. */
            multistate(easy, CURLM_STATE_PROTOCONNECT);
          }
          else {
            /* after the connect has completed, go DO */
            multistate(easy, CURLM_STATE_DO);
            result = CURLM_CALL_MULTI_PERFORM;
          }
        }
        break;

      case CURLM_STATE_PROTOCONNECT:
        /* protocol-specific connect phase */
        easy->result = Curl_protocol_connecting(easy->easy_conn,
                                                &protocol_connect);
        if(protocol_connect) {
          /* after the connect has completed, go DO */
          multistate(easy, CURLM_STATE_DO);
          result = CURLM_CALL_MULTI_PERFORM;
        }
        else if(easy->result) {
          /* failure detected */
          Curl_posttransfer(easy->easy_handle);
          Curl_done(&easy->easy_conn, easy->result);
          Curl_disconnect(easy->easy_conn); /* close the connection */
          easy->easy_conn = NULL;           /* no more connection */
        }
        break;

      case CURLM_STATE_DO:
        /* Perform the protocol's DO action */
        easy->result = Curl_do(&easy->easy_conn, &dophase_done);

        if(CURLE_OK == easy->result) {

          if(!dophase_done) {
            /* DO was not completed in one function call, we must continue
               DOING... */
            multistate(easy, CURLM_STATE_DOING);
            result = CURLM_OK;
          }

          /* after DO, go PERFORM... or DO_MORE */
          else if(easy->easy_conn->bits.do_more) {
            /* we're supposed to do more, but we need to sit down, relax
               and wait a little while first */
            multistate(easy, CURLM_STATE_DO_MORE);
            result = CURLM_OK;
          }
          else {
            /* we're done with the DO, now PERFORM */
            easy->result = Curl_readwrite_init(easy->easy_conn);
            if(CURLE_OK == easy->result) {
              multistate(easy, CURLM_STATE_PERFORM);
              result = CURLM_CALL_MULTI_PERFORM;
            }
          }
        }
        else {
          /* failure detected */
          Curl_posttransfer(easy->easy_handle);
          Curl_done(&easy->easy_conn, easy->result);
          Curl_disconnect(easy->easy_conn); /* close the connection */
          easy->easy_conn = NULL;           /* no more connection */
        }
        break;

      case CURLM_STATE_DOING:
        /* we continue DOING until the DO phase is complete */
        easy->result = Curl_protocol_doing(easy->easy_conn, &dophase_done);
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
              /* we're done with the DO, now PERFORM */
              easy->result = Curl_readwrite_init(easy->easy_conn);
              if(CURLE_OK == easy->result) {
                multistate(easy, CURLM_STATE_PERFORM);
                result = CURLM_CALL_MULTI_PERFORM;
              }
            }
          } /* dophase_done */
        }
        else {
          /* failure detected */
          Curl_posttransfer(easy->easy_handle);
          Curl_done(&easy->easy_conn, easy->result);
          Curl_disconnect(easy->easy_conn); /* close the connection */
          easy->easy_conn = NULL;           /* no more connection */
        }
        break;

      case CURLM_STATE_DO_MORE:
        /* Ready to do more? */
        easy->result = Curl_is_connected(easy->easy_conn, SECONDARYSOCKET,
                                         &connected);
        if(connected) {
          /*
           * When we are connected, DO MORE and then go PERFORM
           */
          easy->result = Curl_do_more(easy->easy_conn);

          if(CURLE_OK == easy->result)
            easy->result = Curl_readwrite_init(easy->easy_conn);

          if(CURLE_OK == easy->result) {
            multistate(easy, CURLM_STATE_PERFORM);
            result = CURLM_CALL_MULTI_PERFORM;
          }
        }
        break;

      case CURLM_STATE_PERFORM:
        /* read/write data if it is ready to do so */
        easy->result = Curl_readwrite(easy->easy_conn, &done);

        if(easy->result)  {
          /* The transfer phase returned error, we mark the connection to get
           * closed to prevent being re-used. This is becasue we can't
           * possibly know if the connection is in a good shape or not now. */
          easy->easy_conn->bits.close = TRUE;

          if(CURL_SOCKET_BAD != easy->easy_conn->sock[SECONDARYSOCKET]) {
            /* if we failed anywhere, we must clean up the secondary socket if
               it was used */
            sclose(easy->easy_conn->sock[SECONDARYSOCKET]);
            easy->easy_conn->sock[SECONDARYSOCKET]=-1;
          }
          Curl_posttransfer(easy->easy_handle);
          Curl_done(&easy->easy_conn, easy->result);
        }

        else if(TRUE == done) {
          char *newurl;
          bool retry = Curl_retry_request(easy->easy_conn, &newurl);

          /* call this even if the readwrite function returned error */
          Curl_posttransfer(easy->easy_handle);

          /* When we follow redirects, must to go back to the CONNECT state */
          if(easy->easy_conn->newurl || retry) {
            if(!retry) {
              /* if the URL is a follow-location and not just a retried request
                 then figure out the URL here */
              newurl = easy->easy_conn->newurl;
              easy->easy_conn->newurl = NULL;
            }
            easy->result = Curl_done(&easy->easy_conn, CURLE_OK);
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
        /* post-transfer command */
        easy->result = Curl_done(&easy->easy_conn, CURLE_OK);

        /* after we have DONE what we're supposed to do, go COMPLETED, and
           it doesn't matter what the Curl_done() returned! */
        multistate(easy, CURLM_STATE_COMPLETED);
        break;

      case CURLM_STATE_COMPLETED:
        /* this is a completed transfer, it is likely to still be connected */

        /* This node should be delinked from the list now and we should post
           an information message that we are complete. */
        break;
      default:
        return CURLM_INTERNAL_ERROR;
      }

      if(CURLM_STATE_COMPLETED != easy->state) {
        if(CURLE_OK != easy->result) {
          /*
           * If an error was returned, and we aren't in completed state now,
           * then we go to completed and consider this transfer aborted.  */
          multistate(easy, CURLM_STATE_COMPLETED);
        }
        else
          /* this one still lives! */
          (*running_handles)++;
      }

    } while (easy->easy_handle->change.url_changed);

    if ((CURLM_STATE_COMPLETED == easy->state) && !easy->msg) {
      /* clear out the usage of the shared DNS cache */
      easy->easy_handle->hostcache = NULL;

      /* now add a node to the Curl_message linked list with this info */
      msg = (struct Curl_message *)malloc(sizeof(struct Curl_message));

      if(!msg)
        return CURLM_OUT_OF_MEMORY;

      msg->extmsg.msg = CURLMSG_DONE;
      msg->extmsg.easy_handle = easy->easy_handle;
      msg->extmsg.data.result = easy->result;
      msg->next=NULL;

      easy->msg = msg;
      easy->msg_num = 1; /* there is one unread message here */

      multi->num_msgs++; /* increase message counter */
    }
    easy = easy->next; /* operate on next handle */
  }

  return result;
}