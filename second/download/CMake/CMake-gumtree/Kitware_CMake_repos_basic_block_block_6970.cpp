f(ret) {
      error_strerror(ret, errorbuf, sizeof(errorbuf));
      failf(data, "Error reading CRL file %s - PolarSSL: (-0x%04X) %s",
            SSL_SET_OPTION(CRLfile), -ret, errorbuf);

      return CURLE_SSL_CRL_BADFILE;
    }