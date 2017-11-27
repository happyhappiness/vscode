int parse_identifier_vl(const char *str, value_list_t *vl) /* {{{ */
{
  char str_copy[6 * DATA_MAX_NAME_LEN];
  char *host = NULL;
  char *plugin = NULL;
  char *plugin_instance = NULL;
  char *type = NULL;
  char *type_instance = NULL;
  int status;

  if ((str == NULL) || (vl == NULL))
    return EINVAL;

  sstrncpy(str_copy, str, sizeof(str_copy));

  status = parse_identifier(str_copy, &host, &plugin, &plugin_instance, &type,
                            &type_instance,
                            /* default_host = */ NULL);
  if (status != 0)
    return status;

  sstrncpy(vl->host, host, sizeof(vl->host));
  sstrncpy(vl->plugin, plugin, sizeof(vl->plugin));
  sstrncpy(vl->plugin_instance,
           (plugin_instance != NULL) ? plugin_instance : "",
           sizeof(vl->plugin_instance));
  sstrncpy(vl->type, type, sizeof(vl->type));
  sstrncpy(vl->type_instance, (type_instance != NULL) ? type_instance : "",
           sizeof(vl->type_instance));

  return 0;
}