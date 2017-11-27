static void conn_prepare_vl(value_list_t *vl, value_t *values) {
  vl->values = values;
  vl->values_len = 1;
  sstrncpy(vl->host, hostname_g, sizeof(vl->host));
  sstrncpy(vl->plugin, "tcpconns", sizeof(vl->plugin));
  sstrncpy(vl->type, "tcp_connections", sizeof(vl->type));
}