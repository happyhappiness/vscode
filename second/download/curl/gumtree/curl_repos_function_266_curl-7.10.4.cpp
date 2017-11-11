CURLMcode curl_multi_perform(CURLM *multi_handle, int *running_handles)
{
  struct Curl_multi *multi=(struct Curl_multi *)multi_handle;
  struct Curl_one_easy *easy;
  bool done;
  CURLMcode result=CURLM_OK;
  struct Curl_message *msg = NULL;
  bool connected;

  *running_handles = 0; /* bump this once for every living handle */

  if(!GOOD_MULTI_HANDLE(multi))
    return CURLM_BAD_HANDLE;

  easy=multi->easy.next;
  while(easy) {

#ifdef MALLOCDEBUG
    fprintf(stderr, "HANDLE %p: State: %x\n",
            (char *)easy, easy->state);
#endif

    switch(easy->state) {
    case CURLM_STATE_INIT:
      /* init this transfer. */
      easy->result=Curl_pretransfer(easy->easy_handle);

      if(CURLE_OK == easy->result) {
        /* after init, go CONNECT */
        easy->state = CURLM_STATE_CONNECT;
        result = CURLM_CALL_MULTI_PERFORM; 
        
        easy->easy_handle->state.used_interface = Curl_if_multi;
      }
      break;
    case CURLM_STATE_CONNECT:
      if (Curl_global_host_cache_use(easy->easy_handle)) {
        easy->easy_handle->hostcache = Curl_global_host_cache_get();
      }
      else {
        if (multi->hostcache == NULL)
          multi->hostcache = Curl_hash_alloc(7, Curl_freednsinfo);

        easy->easy_handle->hostcache = multi->hostcache;
      }

      /* Connect. We get a connection identifier filled in. */
      easy->result = Curl_connect(easy->easy_handle, &easy->easy_conn);

      /* after the connect has been sent off, go WAITCONNECT */
      if(CURLE_OK == easy->result) {
        easy->state = CURLM_STATE_WAITCONNECT;
        result = CURLM_CALL_MULTI_PERFORM; 
      }
      break;

    case CURLM_STATE_WAITCONNECT:
      {
        bool connected;
        easy->result = Curl_is_connected(easy->easy_conn,
                                         easy->easy_conn->firstsocket,
                                         &connected);
        if(connected)
          easy->result = Curl_protocol_connect(easy->easy_conn, NULL);

        if(CURLE_OK != easy->result) {
          /* failure detected */
          Curl_disconnect(easy->easy_conn); /* close the connection */
          easy->easy_conn = NULL;           /* no more connection */
          break;
        }

        if(connected) {
          /* after the connect has completed, go DO */
          easy->state = CURLM_STATE_DO;
          result = CURLM_CALL_MULTI_PERFORM; 
        }
      }
      break;

    case CURLM_STATE_DO:
      /* Do the fetch or put request */
      easy->result = Curl_do(&easy->easy_conn);
      if(CURLE_OK == easy->result) {

        /* after do, go PERFORM... or DO_MORE */
        if(easy->easy_conn->bits.do_more) {
          /* we're supposed to do more, but we need to sit down, relax
             and wait a little while first */
          easy->state = CURLM_STATE_DO_MORE;
          result = CURLM_OK;
        }
        else {
          /* we're done with the DO, now PERFORM */
          easy->result = Curl_readwrite_init(easy->easy_conn);
          if(CURLE_OK == easy->result) {
            easy->state = CURLM_STATE_PERFORM;
            result = CURLM_CALL_MULTI_PERFORM; 
          }
        }
      }
      break;

    case CURLM_STATE_DO_MORE:
      /*
       * First, check if we really are ready to do more.
       */
      easy->result = Curl_is_connected(easy->easy_conn,
                                       easy->easy_conn->secondarysocket,
                                       &connected);
      if(connected) {
        /*
         * When we are connected, DO MORE and then go PERFORM
         */
        easy->result = Curl_do_more(easy->easy_conn);

        if(CURLE_OK == easy->result)
          easy->result = Curl_readwrite_init(easy->easy_conn);

        if(CURLE_OK == easy->result) {
          easy->state = CURLM_STATE_PERFORM;
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

        if(-1 !=easy->easy_conn->secondarysocket) {
          /* if we failed anywhere, we must clean up the secondary socket if
             it was used */
          sclose(easy->easy_conn->secondarysocket);
          easy->easy_conn->secondarysocket=-1;
        }
        Curl_posttransfer(easy->easy_handle);
        Curl_done(easy->easy_conn);
      }

      /* after the transfer is done, go DONE */
      else if(TRUE == done) {

        /* call this even if the readwrite function returned error */
        Curl_posttransfer(easy->easy_handle);

        /* When we follow redirects, must to go back to the CONNECT state */
        if(easy->easy_conn->newurl) {
          easy->result = Curl_follow(easy->easy_handle,
                                     strdup(easy->easy_conn->newurl));
          if(CURLE_OK == easy->result) {
            easy->state = CURLM_STATE_CONNECT;
            result = CURLM_CALL_MULTI_PERFORM;
          }
        }
        else {
          easy->state = CURLM_STATE_DONE;
          result = CURLM_CALL_MULTI_PERFORM; 
        }
      }
      break;
    case CURLM_STATE_DONE:
      /* post-transfer command */
      easy->result = Curl_done(easy->easy_conn);

      /* after we have DONE what we're supposed to do, go COMPLETED, and
         it doesn't matter what the Curl_done() returned! */
      easy->state = CURLM_STATE_COMPLETED;
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
      if(CURLE_OK != easy->result)
        /*
         * If an error was returned, and we aren't in completed state now,
         * then we go to completed and consider this transfer aborted.  */
        easy->state = CURLM_STATE_COMPLETED;
      else
        /* this one still lives! */
        (*running_handles)++;
    }

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