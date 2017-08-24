{
        failf(data, "SSL: SSLSetCertificate() failed: OSStatus %d", err);
        return CURLE_SSL_CERTPROBLEM;
      }