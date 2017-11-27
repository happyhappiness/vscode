static int ovs_stats_update_iface(yajl_val iface) {
  if (!iface || !YAJL_IS_OBJECT(iface)) {
    ERROR("ovs_stats plugin: incorrect JSON port data");
    return -1;
  }

  yajl_val row = ovs_utils_get_value_by_key(iface, "new");
  if (!row || !YAJL_IS_OBJECT(row))
    return 0;

  yajl_val iface_name = ovs_utils_get_value_by_key(row, "name");
  if (!iface_name || !YAJL_IS_STRING(iface_name))
    return 0;

  port_list_t *port = ovs_stats_get_port_by_name(YAJL_GET_STRING(iface_name));
  if (port == NULL)
    return 0;

  yajl_val iface_stats = ovs_utils_get_value_by_key(row, "statistics");
  yajl_val iface_ext_ids = ovs_utils_get_value_by_key(row, "external_ids");
  yajl_val iface_uuid = ovs_utils_get_value_by_key(row, "_uuid");
  /*
   * {
        "statistics": [
          "map",
          [
            [
              "collisions",
              0
            ],
            . . .
            [
              "tx_packets",
              0
            ]
          ]
        ]
      }
   Check that statistics is an array with 2 elements
   */
  if (iface_stats && YAJL_IS_ARRAY(iface_stats) &&
      YAJL_GET_ARRAY(iface_stats)->len == 2)
    ovs_stats_update_iface_stats(port, YAJL_GET_ARRAY(iface_stats)->values[1]);
  if (iface_ext_ids && YAJL_IS_ARRAY(iface_ext_ids))
    ovs_stats_update_iface_ext_ids(port,
                                   YAJL_GET_ARRAY(iface_ext_ids)->values[1]);
  if (iface_uuid && YAJL_IS_ARRAY(iface_uuid) &&
      YAJL_GET_ARRAY(iface_uuid)->len == 2)
    sstrncpy(port->iface_uuid,
             YAJL_GET_STRING(YAJL_GET_ARRAY(iface_uuid)->values[1]),
             sizeof(port->iface_uuid));

  return 0;
}