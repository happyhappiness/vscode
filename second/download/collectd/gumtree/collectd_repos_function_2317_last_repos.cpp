static int cr_config_router(oconfig_item_t *ci) /* {{{ */
{
  cr_data_t *router_data;
  char read_name[128];
  int status;

  router_data = calloc(1, sizeof(*router_data));
  if (router_data == NULL)
    return -1;
  router_data->connection = NULL;
  router_data->node = NULL;
  router_data->service = NULL;
  router_data->username = NULL;
  router_data->password = NULL;

  status = 0;
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Host", child->key) == 0)
      status = cf_util_get_string(child, &router_data->node);
    else if (strcasecmp("Port", child->key) == 0)
      status = cf_util_get_service(child, &router_data->service);
    else if (strcasecmp("User", child->key) == 0)
      status = cf_util_get_string(child, &router_data->username);
    else if (strcasecmp("Password", child->key) == 0)
      status = cf_util_get_string(child, &router_data->password);
    else if (strcasecmp("CollectInterface", child->key) == 0)
      cf_util_get_boolean(child, &router_data->collect_interface);
    else if (strcasecmp("CollectRegistrationTable", child->key) == 0)
      cf_util_get_boolean(child, &router_data->collect_regtable);
#if ROS_VERSION >= ROS_VERSION_ENCODE(1, 1, 0)
    else if (strcasecmp("CollectCPULoad", child->key) == 0)
      cf_util_get_boolean(child, &router_data->collect_cpu_load);
    else if (strcasecmp("CollectMemory", child->key) == 0)
      cf_util_get_boolean(child, &router_data->collect_memory);
    else if (strcasecmp("CollectDF", child->key) == 0)
      cf_util_get_boolean(child, &router_data->collect_df);
    else if (strcasecmp("CollectDisk", child->key) == 0)
      cf_util_get_boolean(child, &router_data->collect_disk);
#endif
    else {
      WARNING("routeros plugin: Unknown config option `%s'.", child->key);
    }

    if (status != 0)
      break;
  }

  if (status == 0) {
    if (router_data->node == NULL) {
      ERROR("routeros plugin: No `Host' option within a `Router' block. "
            "Where should I connect to?");
      status = -1;
    }

    if (router_data->password == NULL) {
      ERROR("routeros plugin: No `Password' option within a `Router' block. "
            "How should I authenticate?");
      status = -1;
    }

    if (!router_data->collect_interface && !router_data->collect_regtable) {
      ERROR("routeros plugin: No `Collect*' option within a `Router' block. "
            "What statistics should I collect?");
      status = -1;
    }
  }

  if ((status == 0) && (router_data->username == NULL)) {
    router_data->username = sstrdup("admin");
    if (router_data->username == NULL) {
      ERROR("routeros plugin: sstrdup failed.");
      status = -1;
    }
  }

  if (status != 0) {
    cr_free_data(router_data);
    return status;
  }

  snprintf(read_name, sizeof(read_name), "routeros/%s", router_data->node);
  return plugin_register_complex_read(
      /* group = */ NULL, read_name, cr_read, /* interval = */ 0,
      &(user_data_t){
          .data = router_data, .free_func = (void *)cr_free_data,
      });
}