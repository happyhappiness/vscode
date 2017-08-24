{
#if (ARES_VERSION >= 0x010704)
  struct in_addr a4;

  if((!local_ip4) || (local_ip4[0] == 0)) {
    a4.s_addr = 0; /* disabled: do not bind to a specific address */
  }
  else {
    if(Curl_inet_pton(AF_INET, local_ip4, &a4) != 1) {
      return CURLE_BAD_FUNCTION_ARGUMENT;
    }
  }

  ares_set_local_ip4((ares_channel)data->state.resolver, ntohl(a4.s_addr));

  return CURLE_OK;
#else /* c-ares version too old! */
  (void)data;
  (void)local_ip4;
  return CURLE_NOT_BUILT_IN;
#endif
}