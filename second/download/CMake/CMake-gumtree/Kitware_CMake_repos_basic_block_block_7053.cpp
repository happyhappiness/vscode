f(Curl_inet_pton(AF_INET, hostname, &addr)
#ifdef ENABLE_IPV6
     || Curl_inet_pton(AF_INET6, hostname, &addr6)
#endif
    ) {
    infof(data, "schannel: using IP address, SNI is not supported by OS.\n");
  }