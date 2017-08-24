{
    /* only cleanup if we did a previous init */
    curlssl_cleanup();
    init_ssl = FALSE;
  }