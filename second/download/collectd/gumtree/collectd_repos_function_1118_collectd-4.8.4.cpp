static void olsrd_set_service (const char *service) /* {{{ */
{
  char *tmp;
  if (service == NULL)
    return;
  tmp = strdup (service);
  if (tmp == NULL)
    return;
  config_service = tmp;
}