static void ovs_stats_bridge_table_change_cb(yajl_val jupdates) {
  /* Bridge Table update example JSON data
    {
      "Bridge": {
        "bb1f8965-5775-46d9-b820-236ca8edbedc": {
          "new": {
            "name": "br0",
            "ports": [
              "set",
              [
                [
                  "uuid",
                  "117f1a07-7ef0-458a-865c-ec7fbb85bc01"
                ],
                [
                  "uuid",
                  "12fd8bdc-e950-4281-aaa9-46e185658f79"
                ]
              ]
            ]
          }
        }
      }
    }
   */
  const char *path[] = {"Bridge", NULL};

  yajl_val bridges = yajl_tree_get(jupdates, path, yajl_t_object);

  if (bridges && YAJL_IS_OBJECT(bridges)) {
    for (size_t i = 0; i < YAJL_GET_OBJECT(bridges)->len; i++) {
      yajl_val bridge = YAJL_GET_OBJECT(bridges)->values[i];
      ovs_stats_update_bridge(bridge);
    }
  }
}