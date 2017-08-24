{
        /* Head back to the CONNECT state */
        multistate(data, CURLM_STATE_CONNECT);
        rc = CURLM_CALL_MULTI_PERFORM;
        result = CURLE_OK;
      }