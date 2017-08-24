f(HEADER_OVERFLOW(nva[1])) {
    failf(conn->data, "Failed sending HTTP request: Header overflow");
    goto fail;
  }