static int snmp_agent_register_oid(oid_t *oid, Netsnmp_Node_Handler *handler) {
  netsnmp_handler_registration *reg;
  char *oid_name = snmp_agent_get_oid_name(oid->oid, oid->oid_len - 1);
  char oid_str[DATA_MAX_NAME_LEN];

  snmp_agent_oid_to_string(oid_str, sizeof(oid_str), oid);

  if (oid_name == NULL) {
    WARNING(PLUGIN_NAME
            ": Skipped registration: OID (%s) is not found in main tree",
            oid_str);
    return 0;
  }

  reg = netsnmp_create_handler_registration(oid_name, handler, oid->oid,
                                            oid->oid_len, HANDLER_CAN_RONLY);
  if (reg == NULL) {
    ERROR(PLUGIN_NAME ": Failed to create handler registration for OID (%s)",
          oid_str);
    return -1;
  }

  pthread_mutex_lock(&g_agent->agentx_lock);

  if (netsnmp_register_instance(reg) != MIB_REGISTERED_OK) {
    ERROR(PLUGIN_NAME ": Failed to register handler for OID (%s)", oid_str);
    pthread_mutex_unlock(&g_agent->agentx_lock);
    return -1;
  }

  pthread_mutex_unlock(&g_agent->agentx_lock);

  DEBUG(PLUGIN_NAME ": Registered handler for OID (%s)", oid_str);

  return 0;
}