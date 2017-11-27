static void conn_submit_port_total(void) {
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  conn_prepare_vl(&vl, values);

  sstrncpy(vl.plugin_instance, "all", sizeof(vl.plugin_instance));

  for (int i = 1; i <= TCP_STATE_MAX; i++) {
    vl.values[0].gauge = count_total[i];

    sstrncpy(vl.type_instance, tcp_state[i], sizeof(vl.type_instance));

    plugin_dispatch_values(&vl);
  }
}