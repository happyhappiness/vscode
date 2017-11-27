static void conn_submit_port_entry (port_entry_t *pe)
{
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;
  int i;

  vl.values = values;
  vl.values_len = 1;
  sstrncpy (vl.host, hostname_g, sizeof (vl.host));
  sstrncpy (vl.plugin, "tcpconns", sizeof (vl.plugin));
  sstrncpy (vl.type, "tcp_connections", sizeof (vl.type));

  if (((port_collect_listening != 0) && (pe->flags & PORT_IS_LISTENING))
      || (pe->flags & PORT_COLLECT_LOCAL))
  {
    ssnprintf (vl.plugin_instance, sizeof (vl.plugin_instance),
	"%"PRIu16"-local", pe->port);

    for (i = 1; i <= TCP_STATE_MAX; i++)
    {
      vl.values[0].gauge = pe->count_local[i];

      sstrncpy (vl.type_instance, tcp_state[i], sizeof (vl.type_instance));

      plugin_dispatch_values (&vl);
    }
  }

  if (pe->flags & PORT_COLLECT_REMOTE)
  {
    ssnprintf (vl.plugin_instance, sizeof (vl.plugin_instance),
	"%"PRIu16"-remote", pe->port);

    for (i = 1; i <= TCP_STATE_MAX; i++)
    {
      vl.values[0].gauge = pe->count_remote[i];

      sstrncpy (vl.type_instance, tcp_state[i], sizeof (vl.type_instance));

      plugin_dispatch_values (&vl);
    }
  }
}