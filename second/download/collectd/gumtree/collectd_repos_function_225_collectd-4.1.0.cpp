static int csnmp_read_host (host_definition_t *host)
{
  int i;

  DEBUG ("snmp plugin: csnmp_read_host (%s);", host->name);

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

  return (0);
}