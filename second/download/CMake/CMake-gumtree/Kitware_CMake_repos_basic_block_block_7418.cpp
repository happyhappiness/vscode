f(len < 0) {
      free(dnsname);
      return CURLE_OUT_OF_MEMORY;
    }