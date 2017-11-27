static void service_statnode_add(const char *name, /* {{{ */
    const char *host,
    const char *server,
    const char *script)
{
  pinba_statnode_t *node;
  
  node = realloc (stat_nodes,
      sizeof (*stat_nodes) * (stat_nodes_num + 1));
  if (node == NULL)
  {
    ERROR ("pinba plugin: realloc failed");
    return;
  }
  stat_nodes = node;

  node = stat_nodes + stat_nodes_num;
  memset (node, 0, sizeof (*node));
  
  /* reset strings */
  node->name   = NULL;
  node->host   = NULL;
  node->server = NULL;
  node->script = NULL;

  node->mem_peak = NAN;
  
  /* fill query data */
  strset (&node->name, name);
  strset (&node->host, host);
  strset (&node->server, server);
  strset (&node->script, script);
  
  /* increment counter */
  stat_nodes_num++;
}