static void ovs_stats_interface_table_change_cb(yajl_val jupdates) {
  /* Interface Table update example JSON data
    {
      "Interface": {
        "33a289a0-1d34-4e46-a3c2-3e4066fbecc6": {
          "new": {
            "name": "br1",
            "statistics": [
              "map",
              [
                [
                  "collisions",
                  0
                ],
                [
                  "rx_bytes",
                  0
                ],
               . . .
                [
                  "tx_packets",
                  12617
                ]
              ]
            ],
            "_uuid": [
              "uuid",
              "33a289a0-1d34-4e46-a3c2-3e4066fbecc6"
            ]
            "external_ids": [
                "map",
                [
                  [
                    "attached-mac",
                    "fa:16:3e:7c:1c:4b"
                  ],
                  [
                    "iface-id",
                    "a61b7e2b-6951-488a-b4c6-6e91343960b2"
                  ],
                  [
                    "iface-status",
                    "active"
                  ]
                ]
              ]
          }
        }
      }
    }
   */
  const char *path[] = {"Interface", NULL};
  yajl_val ports = yajl_tree_get(jupdates, path, yajl_t_object);
  pthread_mutex_lock(&g_stats_lock);
  if (ports && YAJL_IS_OBJECT(ports))
    for (size_t i = 0; i < YAJL_GET_OBJECT(ports)->len; i++)
      ovs_stats_update_iface(YAJL_GET_OBJECT(ports)->values[i]);
  pthread_mutex_unlock(&g_stats_lock);
  return;
}