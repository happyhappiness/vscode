f(ssl_cafile && verifypeer) {
    bool is_cert_file = is_file(ssl_cafile);

    if(!is_cert_file) {
      failf(data, "SSL: can't load CA certificate file %s", ssl_cafile);
      return CURLE_SSL_CACERT_BADFILE;
    }
  }