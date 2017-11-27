static int snmp_agent_free_config(void) {

  if (g_agent == NULL)
    return -EINVAL;

  for (llentry_t *te = llist_head(g_agent->tables); te != NULL; te = te->next)
    snmp_agent_free_table((table_definition_t **)&te->value);
  llist_destroy(g_agent->tables);

  for (llentry_t *de = llist_head(g_agent->scalars); de != NULL; de = de->next)
    snmp_agent_free_data((data_definition_t **)&de->value);
  llist_destroy(g_agent->scalars);

  return 0;
}