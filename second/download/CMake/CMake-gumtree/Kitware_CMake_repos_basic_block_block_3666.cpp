{
#if (ARES_VERSION >= 0x010704) && defined(ENABLE_IPV6)
  unsigned char a6[INET6_ADDRSTRLEN];

  if((!local_ip6) || (local_ip6[0] == 0)) {
    /* disabled: do not bind to a specific address */
    memset(a6, 0, sizeof(a6));
  }
  else {
    if(Curl_inet_pton(AF_INET6, local_ip6, a6) != 1) {
      return CURLE_BAD_FUNCTION_ARGUMENT;
    }
  }

  ares_set_local_ip6((ares_channel)data->state.resolver, a6);

  return CURLE_OK;
#else /* c-ares version too old! */
  (void)data;
  (void)local_ip6;
  return CURLE_NOT_BUILT_IN;
#endif
}