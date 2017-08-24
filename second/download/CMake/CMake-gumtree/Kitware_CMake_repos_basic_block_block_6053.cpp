f(proxytype == CURLPROXY_HTTPS) {
    failf(data, "Unsupported proxy \'%s\'"
                ", libcurl is built without the HTTPS-proxy support.", proxy);
    return CURLE_NOT_BUILT_IN;
  }