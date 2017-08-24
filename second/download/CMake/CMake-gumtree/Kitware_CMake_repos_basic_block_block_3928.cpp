f(initialized) {
    /* Already initialized, don't do it again, but bump the variable anyway to
       work like curl_global_init() and require the same amount of cleanup
       calls. */
    initialized++;
    return CURLE_OK;
  }