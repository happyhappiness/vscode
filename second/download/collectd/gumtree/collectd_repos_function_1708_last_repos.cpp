void module_register(void) {
  plugin_register_init(PLUGIN_NAME, snmp_agent_init);
  plugin_register_complex_config(PLUGIN_NAME, snmp_agent_config);
}