f(stat(capath, &st) == -1)
      return CURLE_SSL_CACERT_BADFILE;