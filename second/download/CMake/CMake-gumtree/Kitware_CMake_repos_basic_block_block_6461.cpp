f((Curl_inet_pton(AF_INET, hostname, &addr))
  #ifdef ENABLE_IPV6
    || (Curl_inet_pton(AF_INET6, hostname, &addr))
  #endif
       ) {
      infof(data, "WARNING: using IP address, SNI is being disabled by "
            "the OS.\n");
    }