CURLcode Curl_set_dns_interface(struct Curl_easy *data,
                                const char *interf)
{
#if (ARES_VERSION >= 0x010704)
  if(!interf)
    interf = "";

  ares_set_local_dev((ares_channel)data->state.resolver, interf);

  return CURLE_OK;
#else /* c-ares version too old! */
  (void)data;
  (void)interf;
  return CURLE_NOT_BUILT_IN;
#endif
}