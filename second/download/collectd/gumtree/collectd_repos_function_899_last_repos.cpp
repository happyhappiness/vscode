static int config_add_instance(oconfig_item_t *ci) {
  int status = 0;

  /* Disable automatic generation of default instance in the init callback. */
  memcached_have_instances = 1;

  memcached_t *st = calloc(1, sizeof(*st));
  if (st == NULL) {
    ERROR("memcached plugin: calloc failed.");
    return ENOMEM;
  }

  st->name = NULL;
  st->host = NULL;
  st->socket = NULL;
  st->connhost = NULL;
  st->connport = NULL;

  st->fd = -1;

  if (strcasecmp(ci->key, "Instance") == 0)
    status = cf_util_get_string(ci, &st->name);

  if (status != 0) {
    sfree(st);
    return status;
  }

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Socket", child->key) == 0)
      status = cf_util_get_string(child, &st->socket);
    else if (strcasecmp("Host", child->key) == 0)
      status = cf_util_get_string(child, &st->host);
    else if (strcasecmp("Address", child->key) == 0)
      status = cf_util_get_string(child, &st->connhost);
    else if (strcasecmp("Port", child->key) == 0)
      status = cf_util_get_service(child, &st->connport);
    else {
      WARNING("memcached plugin: Option `%s' not allowed here.", child->key);
      status = -1;
    }

    if (status != 0)
      break;
  }

  if (status != 0) {
    memcached_free(st);
    return -1;
  }

  return memcached_add_read_callback(st);
}