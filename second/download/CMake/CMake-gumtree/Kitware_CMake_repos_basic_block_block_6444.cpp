{
    SSLProtocol darwin_ver_min = kTLSProtocol1;
    SSLProtocol darwin_ver_max = kTLSProtocol1;
    CURLcode result = darwinssl_version_from_curl(&darwin_ver_min,
                                                  ssl_version);
    if(result) {
      failf(data, "unsupported min version passed via CURLOPT_SSLVERSION");
      return result;
    }
    result = darwinssl_version_from_curl(&darwin_ver_max,
                                         ssl_version_max >> 16);
    if(result) {
      failf(data, "unsupported max version passed via CURLOPT_SSLVERSION");
      return result;
    }

    (void)SSLSetProtocolVersionMin(connssl->ssl_ctx, darwin_ver_min);
    (void)SSLSetProtocolVersionMax(connssl->ssl_ctx, darwin_ver_max);
    return result;
  }