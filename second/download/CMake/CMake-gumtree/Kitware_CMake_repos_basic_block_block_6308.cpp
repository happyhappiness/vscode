f(!chlg) {
    infof(data, "GSSAPI handshake failure (empty security message)\n");

    return CURLE_BAD_CONTENT_ENCODING;
  }