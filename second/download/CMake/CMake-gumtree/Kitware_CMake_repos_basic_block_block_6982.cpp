{
    ret = x509_crt_parse_file(&connssl->cacert,
                              SSL_CONN_CONFIG(CAfile));

    if(ret<0) {
      error_strerror(ret, errorbuf, sizeof(errorbuf));
      failf(data, "Error reading ca cert file %s - PolarSSL: (-0x%04X) %s",
            SSL_CONN_CONFIG(CAfile), -ret, errorbuf);

      if(SSL_CONN_CONFIG(verifypeer))
        return CURLE_SSL_CACERT_BADFILE;
    }
  }