static char *ovs_events_get_select_params() {
  size_t buff_size = 0;
  size_t buff_off = 0;
  char *opt_buff = NULL;
  static const char params_fmt[] = "[\"Open_vSwitch\"%s]";
  static const char option_fmt[] =
      ",{\"op\":\"select\",\"table\":\"Interface\","
      "\"where\":[[\"name\",\"==\",\"%s\"]],"
      "\"columns\":[\"link_state\",\"external_ids\","
      "\"name\",\"_uuid\"]}";
  static const char default_opt[] =
      ",{\"op\":\"select\",\"table\":\"Interface\","
      "\"where\":[],\"columns\":[\"link_state\","
      "\"external_ids\",\"name\",\"_uuid\"]}";
  /* setup OVS DB interface condition */
  for (ovs_events_iface_list_t *iface = ovs_events_ctx.config.ifaces; iface;
       iface = iface->next) {
    /* allocate new buffer (format size + ifname len is good enough) */
    buff_size += sizeof(option_fmt) + strlen(iface->name);
    char *new_buff = realloc(opt_buff, buff_size);
    if (new_buff == NULL) {
      sfree(opt_buff);
      return NULL;
    }
    opt_buff = new_buff;
    int ret = snprintf(opt_buff + buff_off, buff_size - buff_off, option_fmt,
                       iface->name);
    if (ret < 0) {
      sfree(opt_buff);
      return NULL;
    }
    buff_off += ret;
  }
  /* if no interfaces are configured, use default params */
  if (opt_buff == NULL)
    if ((opt_buff = strdup(default_opt)) == NULL)
      return NULL;

  /* allocate memory for OVS DB select params */
  size_t params_size = sizeof(params_fmt) + strlen(opt_buff);
  char *params_buff = calloc(1, params_size);
  if (params_buff == NULL) {
    sfree(opt_buff);
    return NULL;
  }

  /* create OVS DB select params */
  if (snprintf(params_buff, params_size, params_fmt, opt_buff) < 0)
    sfree(params_buff);

  sfree(opt_buff);
  return params_buff;
}