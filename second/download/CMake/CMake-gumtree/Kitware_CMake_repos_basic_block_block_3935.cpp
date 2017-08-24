f(result) {
      /* something in the global init failed, return nothing */
      DEBUGF(fprintf(stderr, "Error: curl_global_init failed\n"));
      return NULL;
    }