static void ovs_stats_initialize(ovs_db_t *pdb) {
  const char *bridge_columns[] = {"name", "ports", NULL};
  const char *port_columns[] = {"name", "interfaces", NULL};
  const char *interface_columns[] = {"name", "statistics", "_uuid",
                                     "external_ids", NULL};

  /* subscribe to a tables */
  ovs_db_table_cb_register(
      pdb, "Bridge", bridge_columns, ovs_stats_bridge_table_change_cb,
      ovs_stats_bridge_table_result_cb,
      OVS_DB_TABLE_CB_FLAG_INITIAL | OVS_DB_TABLE_CB_FLAG_INSERT |
          OVS_DB_TABLE_CB_FLAG_MODIFY);

  ovs_db_table_cb_register(pdb, "Bridge", bridge_columns,
                           ovs_stats_bridge_table_delete_cb, NULL,
                           OVS_DB_TABLE_CB_FLAG_DELETE);

  ovs_db_table_cb_register(
      pdb, "Port", port_columns, ovs_stats_port_table_change_cb,
      ovs_stats_port_table_result_cb,
      OVS_DB_TABLE_CB_FLAG_INITIAL | OVS_DB_TABLE_CB_FLAG_INSERT |
          OVS_DB_TABLE_CB_FLAG_MODIFY);

  ovs_db_table_cb_register(pdb, "Port", port_columns,
                           ovs_stats_port_table_delete_cb, NULL,
                           OVS_DB_TABLE_CB_FLAG_DELETE);

  ovs_db_table_cb_register(
      pdb, "Interface", interface_columns, ovs_stats_interface_table_change_cb,
      ovs_stats_interface_table_result_cb,
      OVS_DB_TABLE_CB_FLAG_INITIAL | OVS_DB_TABLE_CB_FLAG_INSERT |
          OVS_DB_TABLE_CB_FLAG_MODIFY);
}