{
      /* no need to continue if time already is up */
      failf(data, "SSL/TLS connection timeout");
      return CURLE_OPERATION_TIMEDOUT;
    }