{
      infof(data, "SPNEGO handshake failure (empty challenge message)\n");

      return CURLE_BAD_CONTENT_ENCODING;
    }