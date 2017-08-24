{
      error_strerror(ret, errorbuf, sizeof(errorbuf));
      failf(data, "Error reading private key %s - PolarSSL: (-0x%04X) %s",
            SSL_SET_OPTION(key), -ret, errorbuf);

      return CURLE_SSL_CERTPROBLEM;
    }