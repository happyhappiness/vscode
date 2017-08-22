    }

  if(flags & CURL_GLOBAL_WIN32)
    if(win32_init() != CURLE_OK) {
      DEBUGF(fprintf(stderr, "Error: win32_init failed\n"));
      return CURLE_FAILED_INIT;
    }
