static const char *olsrd_get_service(void) /* {{{ */
{
  if (config_service != NULL)
    return config_service;
  return OLSRD_DEFAULT_SERVICE;
}