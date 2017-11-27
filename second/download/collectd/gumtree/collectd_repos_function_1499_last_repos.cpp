static void domain_connection_change_handler(ipmi_domain_t *domain, int err,
                                             unsigned int conn_num,
                                             unsigned int port_num,
                                             int still_connected,
                                             void *user_data) {

  DEBUG("domain_connection_change_handler (domain = %p, err = %i, "
        "conn_num = %u, port_num = %u, still_connected = %i, "
        "user_data = %p);",
        (void *)domain, err, conn_num, port_num, still_connected, user_data);

  c_ipmi_instance_t *st = user_data;

  if (err != 0)
    c_ipmi_error(st, "domain_connection_change_handler", err);

  if (!still_connected) {

    if (st->notify_conn && st->connected && st->init_in_progress == 0) {
      notification_t n = c_ipmi_notification_init(st, NOTIF_FAILURE);

      sstrncpy(n.message, "IPMI connection lost", sizeof(n.plugin));

      plugin_dispatch_notification(&n);
    }

    st->connected = 0;
    return;
  }

  if (st->notify_conn && !st->connected && st->init_in_progress == 0) {
    notification_t n = c_ipmi_notification_init(st, NOTIF_OKAY);

    sstrncpy(n.message, "IPMI connection restored", sizeof(n.plugin));

    plugin_dispatch_notification(&n);
  }

  st->connected = 1;

  int status = ipmi_domain_add_entity_update_handler(
      domain, domain_entity_update_handler, /* user data = */ st);
  if (status != 0) {
    c_ipmi_error(st, "ipmi_domain_add_entity_update_handler", status);
  }

  status = st->connection->add_event_handler(st->connection, smi_event_handler,
                                             (void *)domain);

  if (status != 0)
    c_ipmi_error(st, "Failed to register smi event handler", status);
}