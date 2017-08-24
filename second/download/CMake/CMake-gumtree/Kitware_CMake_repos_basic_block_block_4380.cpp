f(check <= 0) {
          failf(data, "Proxy CONNECT aborted due to timeout");
          error = SELECT_TIMEOUT; /* already too little time */
          break;
        }