{
        /* Grabbed the channel */
        multistate(data, CURLM_STATE_DO);
        rc = CURLM_CALL_MULTI_PERFORM;
      }