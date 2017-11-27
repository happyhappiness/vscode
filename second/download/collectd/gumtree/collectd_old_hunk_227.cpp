    unsigned int port_num,
    int still_connected,
    void *user_data)
{
  int status;

  printf ("domain_connection_change_handler (domain = %p, err = %i, "
      "conn_num = %u, port_num = %u, still_connected = %i, "
      "user_data = %p);\n",
      (void *) domain, err, conn_num, port_num, still_connected, user_data);

  status = ipmi_domain_add_entity_update_handler (domain,
      domain_entity_update_handler, /* user data = */ NULL);
