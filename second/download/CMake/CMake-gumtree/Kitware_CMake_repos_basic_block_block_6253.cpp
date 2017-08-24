{
    infof(data, "DIGEST-MD5 handshake failure (empty challenge message)\n");

    return CURLE_BAD_CONTENT_ENCODING;
  }