{
        /* Grabbed the channel */
        multistate(data, CURLM_STATE_PERFORM);
        rc = CURLM_CALL_MULTI_PERFORM;
      }