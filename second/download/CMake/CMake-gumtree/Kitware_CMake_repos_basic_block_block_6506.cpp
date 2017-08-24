{
    case errSSLXCertChainInvalid:
      failf(data, "SSL certificate problem: Invalid certificate chain");
      return CURLE_SSL_CACERT;
    case errSSLUnknownRootCert:
      failf(data, "SSL certificate problem: Untrusted root certificate");
      return CURLE_SSL_CACERT;
    case errSSLNoRootCert:
      failf(data, "SSL certificate problem: No root certificate");
      return CURLE_SSL_CACERT;
    case errSSLCertExpired:
      failf(data, "SSL certificate problem: Certificate chain had an "
            "expired certificate");
      return CURLE_SSL_CACERT;
    case errSSLBadCert:
      failf(data, "SSL certificate problem: Couldn't understand the server "
            "certificate format");
      return CURLE_SSL_CONNECT_ERROR;
    case errSSLHostNameMismatch:
      failf(data, "SSL certificate peer hostname mismatch");
      return CURLE_PEER_FAILED_VERIFICATION;
    default:
      failf(data, "SSL unexpected certificate error %d", err);
      return CURLE_SSL_CACERT;
  }