{
      failf(data, "Proxy CONNECT aborted due to timeout");
      return CURLE_RECV_ERROR;
    }