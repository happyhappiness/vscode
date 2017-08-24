f(!result) {
      free(newstr);

      return CURLE_BAD_CONTENT_ENCODING;
    }