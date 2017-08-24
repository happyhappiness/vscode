{
  CURLcode result = CURLE_NOT_BUILT_IN;
  int ares_result;

  /* If server is NULL or empty, this would purge all DNS servers
   * from ares library, which will cause any and all queries to fail.
   * So, just return OK if none are configured and don't actually make
   * any changes to c-ares.  This lets c-ares use it's defaults, which
   * it gets from the OS (for instance from /etc/resolv.conf on Linux).
   */
  if(!(servers && servers[0]))
    return CURLE_OK;

#if (ARES_VERSION >= 0x010704)
  ares_result = ares_set_servers_csv(data->state.resolver, servers);
  switch(ares_result) {
  case ARES_SUCCESS:
    result = CURLE_OK;
    break;
  case ARES_ENOMEM:
    result = CURLE_OUT_OF_MEMORY;
    break;
  case ARES_ENOTINITIALIZED:
  case ARES_ENODATA:
  case ARES_EBADSTR:
  default:
    result = CURLE_BAD_FUNCTION_ARGUMENT;
    break;
  }
#else /* too old c-ares version! */
  (void)data;
  (void)(ares_result);
#endif
  return result;
}