static void ovs_stats_port_table_change_cb(yajl_val jupdates) {
  /* Port Table update example JSON data
    {
      "Port": {
        "ab107d6f-28a1-4257-b1cc-5b742821db8a": {
          "new": {
            "name": "br1",
            "interfaces": [
              "uuid",
              "33a289a0-1d34-4e46-a3c2-3e4066fbecc6"
            ]
          }
        }
      }
    }
   */
  const char *path[] = {"Port", NULL};
  yajl_val ports = yajl_tree_get(jupdates, path, yajl_t_object);
  yajl_val port;
  if (ports && YAJL_IS_OBJECT(ports)) {
    for (size_t i = 0; i < YAJL_GET_OBJECT(ports)->len; i++) {
      port = YAJL_GET_OBJECT(ports)->values[i];
      ovs_stats_update_port(YAJL_GET_OBJECT(ports)->keys[i], port);
    }
  }
  return;
}