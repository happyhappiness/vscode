static int c_ipmi_thread_init(c_ipmi_instance_t *st) {
  ipmi_domain_id_t domain_id;
  int status;

  if (st->connaddr != NULL) {
    status = ipmi_ip_setup_con(
        &st->connaddr, &(char *){IPMI_LAN_STD_PORT_STR}, 1, st->authtype,
        (unsigned int)IPMI_PRIVILEGE_USER, st->username, strlen(st->username),
        st->password, strlen(st->password), os_handler,
        /* user data = */ NULL, &st->connection);
    if (status != 0) {
      c_ipmi_error(st, "ipmi_ip_setup_con", status);
      return -1;
    }
  } else {
    status = ipmi_smi_setup_con(/* if_num = */ 0, os_handler,
                                /* user data = */ NULL, &st->connection);
    if (status != 0) {
      c_ipmi_error(st, "ipmi_smi_setup_con", status);
      return -1;
    }
  }

  ipmi_open_option_t opts[] = {
      {.option = IPMI_OPEN_OPTION_ALL, {.ival = 1}},
#ifdef IPMI_OPEN_OPTION_USE_CACHE
      /* OpenIPMI-2.0.17 and later: Disable SDR cache in local file */
      {.option = IPMI_OPEN_OPTION_USE_CACHE, {.ival = 0}},
#endif
  };

  /*
   * NOTE: Domain names must be unique. There is static `domains_list` common
   * to all threads inside lib/domain.c and some ops are done by name.
   */
  status = ipmi_open_domain(
      st->name, &st->connection, /* num_con = */ 1,
      domain_connection_change_handler, /* user data = */ (void *)st,
      /* domain_fully_up_handler = */ NULL, /* user data = */ NULL, opts,
      STATIC_ARRAY_SIZE(opts), &domain_id);
  if (status != 0) {
    c_ipmi_error(st, "ipmi_open_domain", status);
    return -1;
  }

  return 0;
}