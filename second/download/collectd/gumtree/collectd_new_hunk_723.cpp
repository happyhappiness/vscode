  else if (strcasecmp("CollectRoutes", key) == 0)
    olsrd_set_detail(&config_want_routes, value, key);
  else if (strcasecmp("CollectTopology", key) == 0)
    olsrd_set_detail(&config_want_topology, value, key);
  else {
    ERROR("olsrd plugin: Unknown configuration option given: %s", key);
    return -1;
  }

  return 0;
} /* }}} int olsrd_config */

static int olsrd_read(void) /* {{{ */
{
  FILE *fh;
  char buffer[1024];
  size_t buffer_len;

  fh = olsrd_connect();
  if (fh == NULL)
    return -1;

  fputs("\r\n", fh);
  fflush(fh);

  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    buffer_len = strchomp(buffer);
