f(timeout_ms) {
          /* timeout */
          failf(data, "SSL connection timeout at %ld", (long)timeout_ms);
          return CURLE_OPERATION_TIMEDOUT;
        }