f(ret) {
      error_strerror(ret, errorbuf, sizeof(errorbuf));
      failf(data, "Error reading client cert file %s - PolarSSL: (-0x%04X) %s",
            SSL_SET_OPTION(cert), -ret, errorbuf);

      return CURLE_SSL_CERTPROBLEM;
    }