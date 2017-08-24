{
#ifdef ENABLE_IPV6
    struct in6_addr in6;
    if(Curl_inet_pton(AF_INET6, conn->host.name, &in6) > 0) {
      /* This is a numerical IPv6 address, meaning this is a wrongly formatted
         URL */
      failf(data, "IPv6 numerical address used in URL without brackets");
      return CURLE_URL_MALFORMAT;
    }
#endif

    portptr = strchr(conn->host.name, ':');
  }