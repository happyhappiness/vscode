f(s == CURL_SOCKET_BAD)
      /* an IPv6 address was requested but we can't get/use one */
      ipv6_works = 0;
    else {
      ipv6_works = 1;
      Curl_closesocket(NULL, s);
    }