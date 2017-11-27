static int ovs_stats_plugin_config(oconfig_item_t *ci) {
  bridge_list_t *bridge;

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;
    if (strcasecmp("Address", child->key) == 0) {
      if (cf_util_get_string_buffer(child, ovs_stats_cfg.ovs_db_node,
                                    OVS_DB_ADDR_NODE_SIZE) != 0) {
        ERROR("%s: parse '%s' option failed", plugin_name, child->key);
        return -1;
      }
    } else if (strcasecmp("Port", child->key) == 0) {
      if (cf_util_get_string_buffer(child, ovs_stats_cfg.ovs_db_serv,
                                    OVS_DB_ADDR_SERVICE_SIZE) != 0) {
        ERROR("%s: parse '%s' option failed", plugin_name, child->key);
        return -1;
      }
    } else if (strcasecmp("Socket", child->key) == 0) {
      if (cf_util_get_string_buffer(child, ovs_stats_cfg.ovs_db_unix,
                                    OVS_DB_ADDR_UNIX_SIZE) != 0) {
        ERROR("%s: parse '%s' option failed", plugin_name, child->key);
        return -1;
      }
    } else if (strcasecmp("Bridges", child->key) == 0) {
      for (int j = 0; j < child->values_num; j++) {
        /* check value type */
        if (child->values[j].type != OCONFIG_TYPE_STRING) {
          ERROR("%s: Wrong bridge name [idx=%d]. "
                "Bridge name should be string",
                plugin_name, j);
          goto cleanup_fail;
        }
        /* get value */
        char const *br_name = child->values[j].value.string;
        if ((bridge = ovs_stats_get_bridge(g_monitored_bridge_list_head,
                                           br_name)) == NULL) {
          if ((bridge = calloc(1, sizeof(bridge_list_t))) == NULL) {
            ERROR("%s: Error allocating memory for bridge", plugin_name);
            goto cleanup_fail;
          } else {
            char *br_name_dup = strdup(br_name);
            if (br_name_dup == NULL) {
              ERROR("%s: strdup() copy bridge name fail", plugin_name);
              goto cleanup_fail;
            }

            pthread_mutex_lock(&g_stats_lock);
            /* store bridge name */
            bridge->name = br_name_dup;
            bridge->next = g_monitored_bridge_list_head;
            g_monitored_bridge_list_head = bridge;
            pthread_mutex_unlock(&g_stats_lock);
            DEBUG("%s: found monitored interface \"%s\"", plugin_name, br_name);
          }
        }
      }
    } else {
      WARNING("%s: option '%s' not allowed here", plugin_name, child->key);
      goto cleanup_fail;
    }
  }
  return 0;

cleanup_fail:
  ovs_stats_free_bridge_list(g_monitored_bridge_list_head);
  return -1;
}