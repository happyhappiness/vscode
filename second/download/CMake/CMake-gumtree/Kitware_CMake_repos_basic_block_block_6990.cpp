{
      failf(data, "Failed copying public key from peer certificate");
      x509_crt_free(p);
      free(p);
      return CURLE_SSL_PINNEDPUBKEYNOTMATCH;
    }