static c_ipmi_instance_t *c_ipmi_init_instance() {
  c_ipmi_instance_t *st;

  st = calloc(1, sizeof(*st));
  if (st == NULL) {
    ERROR("ipmi plugin: calloc failed.");
    return NULL;
  }

  st->name = strdup("main");
  if (st->name == NULL) {
    sfree(st);
    ERROR("ipmi plugin: strdup() failed.");
    return NULL;
  }

  st->ignorelist = ignorelist_create(/* invert = */ 1);
  if (st->ignorelist == NULL) {
    sfree(st->name);
    sfree(st);
    ERROR("ipmi plugin: ignorelist_create() failed.");
    return NULL;
  }

  st->sensor_list = NULL;
  pthread_mutex_init(&st->sensor_list_lock, /* attr = */ NULL);

  st->host = NULL;
  st->connaddr = NULL;
  st->username = NULL;
  st->password = NULL;
  st->authtype = IPMI_AUTHTYPE_DEFAULT;

  st->next = NULL;

  return st;
}