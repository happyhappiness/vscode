{
    infof(data, "GSSAPI handshake failure (empty security message)\n");

    free(chlg);

    return CURLE_BAD_CONTENT_ENCODING;
  }