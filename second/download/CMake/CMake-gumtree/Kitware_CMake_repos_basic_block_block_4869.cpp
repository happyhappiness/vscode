{
      DEBUGF(infof(data, "multi changed, check CONNECT_PEND queue!\n"));
      Curl_multi_process_pending_handles(multi);
    }