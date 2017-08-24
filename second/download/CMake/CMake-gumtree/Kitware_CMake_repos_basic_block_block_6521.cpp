{
    free(certbuf);
    failf(data, "SSL: out of memory creating CA certificate array");
    return CURLE_OUT_OF_MEMORY;
  }