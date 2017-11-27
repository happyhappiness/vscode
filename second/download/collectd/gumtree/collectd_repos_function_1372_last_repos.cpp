static int pinba_config_view(const oconfig_item_t *ci) /* {{{ */
{
  char *name = NULL;
  char *host = NULL;
  char *server = NULL;
  char *script = NULL;
  int status;

  status = cf_util_get_string(ci, &name);
  if (status != 0)
    return status;

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Host", child->key) == 0)
      status = cf_util_get_string(child, &host);
    else if (strcasecmp("Server", child->key) == 0)
      status = cf_util_get_string(child, &server);
    else if (strcasecmp("Script", child->key) == 0)
      status = cf_util_get_string(child, &script);
    else {
      WARNING("pinba plugin: Unknown config option: %s", child->key);
      status = -1;
    }

    if (status != 0)
      break;
  }

  if (status == 0)
    service_statnode_add(name, host, server, script);

  sfree(name);
  sfree(host);
  sfree(server);
  sfree(script);

  return status;
}