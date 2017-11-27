static int ovs_stats_update_iface_ext_ids(port_list_t *port, yajl_val ext_ids) {
  yajl_val ext_id;
  char *key;
  char *value;

  if (ext_ids && YAJL_IS_ARRAY(ext_ids))
    for (size_t i = 0; i < YAJL_GET_ARRAY(ext_ids)->len; i++) {
      ext_id = YAJL_GET_ARRAY(ext_ids)->values[i];
      if (!YAJL_IS_ARRAY(ext_id))
        return -1;
      key = YAJL_GET_STRING(YAJL_GET_ARRAY(ext_id)->values[0]);
      value = YAJL_GET_STRING(YAJL_GET_ARRAY(ext_id)->values[1]);
      if (key && value) {
        if (strncmp(key, "iface-id", strlen(key)) == 0)
          sstrncpy(port->ex_iface_id, value, sizeof(port->ex_iface_id));
        else if (strncmp(key, "vm-uuid", strlen(key)) == 0)
          sstrncpy(port->ex_vm_id, value, sizeof(port->ex_vm_id));
      }
    }

  return 0;
}