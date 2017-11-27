static int csnmp_read_host (host_definition_t *host)
{
  int i;
  time_t time_start;
  time_t time_end;

  time_start = time (NULL);
  DEBUG ("snmp plugin: csnmp_read_host (%s) started at %u;", host->name,
      (unsigned int) time_start);

  if (host->sess_handle == NULL)
    csnmp_host_open_session (host);

  if (host->sess_handle == NULL)
    return (-1);

  for (i = 0; i < host->data_list_len; i++)
  {
    data_definition_t *data = host->data_list[i];

    if (data->is_table)
      csnmp_read_table (host, data);
    else
      csnmp_read_value (host, data);
  }

  time_end = time (NULL);
  DEBUG ("snmp plugin: csnmp_read_host (%s) finished at %u;", host->name,
      (unsigned int) time_end);
  if ((uint32_t) (time_end - time_start) > host->interval)
  {
    WARNING ("snmp plugin: Host `%s' should be queried every %i seconds, "
	"but reading all values takes %u seconds.",
	host->name, host->interval, (unsigned int) (time_end - time_start));
  }

  return (0);
}