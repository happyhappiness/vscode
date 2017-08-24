f(result == CURLE_FAILED_INIT)
      /* make the error non-fatal if we are not going to verify peer */
      result = CURLE_SSL_CACERT_BADFILE