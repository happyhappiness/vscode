f((0 == Curl_inet_pton(AF_INET, hostname, &addr)) &&
#ifdef ENABLE_IPV6
     (0 == Curl_inet_pton(AF_INET6, hostname, &addr)) &&
#endif
     sni &&
     (gnutls_server_name_set(session, GNUTLS_NAME_DNS, hostname,
                             strlen(hostname)) < 0))
    infof(data, "WARNING: failed to configure server name indication (SNI) "
          "TLS extension\n")