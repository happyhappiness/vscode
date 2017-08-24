{
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