static int cc_add_daemon_config(oconfig_item_t *ci) {
  int ret;
  struct ceph_daemon *nd, cd = {0};
  struct ceph_daemon **tmp;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    WARNING("ceph plugin: `Daemon' blocks need exactly one string "
            "argument.");
    return -1;
  }

  ret = cc_handle_str(ci, cd.name, DATA_MAX_NAME_LEN);
  if (ret) {
    return ret;
  }

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("SocketPath", child->key) == 0) {
      ret = cc_handle_str(child, cd.asok_path, sizeof(cd.asok_path));
      if (ret) {
        return ret;
      }
    } else {
      WARNING("ceph plugin: ignoring unknown option %s", child->key);
    }
  }
  if (cd.name[0] == '\0') {
    ERROR("ceph plugin: you must configure a daemon name.\n");
    return -EINVAL;
  } else if (cd.asok_path[0] == '\0') {
    ERROR("ceph plugin(name=%s): you must configure an administrative "
          "socket path.\n",
          cd.name);
    return -EINVAL;
  } else if (!((cd.asok_path[0] == '/') ||
               (cd.asok_path[0] == '.' && cd.asok_path[1] == '/'))) {
    ERROR("ceph plugin(name=%s): administrative socket paths must begin "
          "with '/' or './' Can't parse: '%s'\n",
          cd.name, cd.asok_path);
    return -EINVAL;
  }

  tmp = realloc(g_daemons, (g_num_daemons + 1) * sizeof(*g_daemons));
  if (tmp == NULL) {
    /* The positive return value here indicates that this is a
     * runtime error, not a configuration error.  */
    return ENOMEM;
  }
  g_daemons = tmp;

  nd = malloc(sizeof(*nd));
  if (!nd) {
    return ENOMEM;
  }
  memcpy(nd, &cd, sizeof(*nd));
  g_daemons[g_num_daemons] = nd;
  g_num_daemons++;
  return 0;
}