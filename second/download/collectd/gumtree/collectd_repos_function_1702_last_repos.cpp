static int snmp_agent_preinit(void) {
  if (g_agent != NULL) {
    /* already initialized if config callback was called before init callback */
    return 0;
  }

  g_agent = calloc(1, sizeof(*g_agent));
  if (g_agent == NULL) {
    ERROR(PLUGIN_NAME ": Failed to allocate memory for snmp agent context");
    return -ENOMEM;
  }

  g_agent->tables = llist_create();
  g_agent->scalars = llist_create();

  if (g_agent->tables == NULL || g_agent->scalars == NULL) {
    ERROR(PLUGIN_NAME ": llist_create() failed");
    llist_destroy(g_agent->scalars);
    llist_destroy(g_agent->tables);
    return -ENOMEM;
  }

  int err;
  /* make us a agentx client. */
  err = netsnmp_ds_set_boolean(NETSNMP_DS_APPLICATION_ID, NETSNMP_DS_AGENT_ROLE,
                               1);
  if (err != 0) {
    ERROR(PLUGIN_NAME ": Failed to set agent role (%d)", err);
    llist_destroy(g_agent->scalars);
    llist_destroy(g_agent->tables);
    return -1;
  }

  /*
   *  For SNMP debug purposes uses snmp_set_do_debugging(1);
   */

  /* initialize the agent library */
  err = init_agent(PLUGIN_NAME);
  if (err != 0) {
    ERROR(PLUGIN_NAME ": Failed to initialize the agent library (%d)", err);
    llist_destroy(g_agent->scalars);
    llist_destroy(g_agent->tables);
    return -1;
  }

  init_snmp(PLUGIN_NAME);

  g_agent->tp = read_all_mibs();

  return 0;
}