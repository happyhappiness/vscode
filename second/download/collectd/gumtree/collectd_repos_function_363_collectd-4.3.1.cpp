static void conn_submit_port_entry (port_entry_t *pe)
{
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;
  int i;

  vl.values = values;
  vl.values_len = 1;
  vl.time = time (NULL);
  strcpy (vl.host, hostname_g);
  strcpy (vl.plugin, "tcpconns");

  if (((port_collect_listening != 0) && (pe->flags & PORT_IS_LISTENING))
      || (pe->flags & PORT_COLLECT_LOCAL))
  {
    snprintf (vl.plugin_instance, sizeof (vl.plugin_instance),
	"%hu-local", pe->port);
    vl.plugin_instance[sizeof (vl.plugin_instance) - 1] = '\0';

    for (i = 1; i <= TCP_STATE_MAX; i++)
    {
      vl.values[0].gauge = pe->count_local[i];

      strncpy (vl.type_instance, tcp_state[i], sizeof (vl.type_instance));
      vl.type_instance[sizeof (vl.type_instance) - 1] = '\0';

      plugin_dispatch_values ("tcp_connections", &vl);
    }
  }

  if (pe->flags & PORT_COLLECT_REMOTE)
  {
    snprintf (vl.plugin_instance, sizeof (vl.plugin_instance),
	"%hu-remote", pe->port);
    vl.plugin_instance[sizeof (vl.plugin_instance) - 1] = '\0';

    for (i = 1; i <= TCP_STATE_MAX; i++)
    {
      vl.values[0].gauge = pe->count_remote[i];

      strncpy (vl.type_instance, tcp_state[i], sizeof (vl.type_instance));
      vl.type_instance[sizeof (vl.type_instance) - 1] = '\0';

      plugin_dispatch_values ("tcp_connections", &vl);
    }
  }
}