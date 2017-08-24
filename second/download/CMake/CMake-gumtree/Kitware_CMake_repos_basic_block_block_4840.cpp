{
        /* after the connect has completed, go WAITDO or DO */
        multistate(data, Curl_pipeline_wanted(multi, CURLPIPE_HTTP1)?
                   CURLM_STATE_WAITDO:CURLM_STATE_DO);
        rc = CURLM_CALL_MULTI_PERFORM;
      }