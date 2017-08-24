{
    infof(data, "NTLM handshake failure (empty type-2 message)\n");

    return CURLE_BAD_CONTENT_ENCODING;
  }