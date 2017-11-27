static int csnmp_read_host (user_data_t *ud)
{
  host_definition_t *host;
  time_t time_start;
  time_t time_end;
  int status;
  int success;
  int i;

  host = ud->data;

  if (host->interval == 0)
    host->interval = interval_g;

  time_start = time (NULL);
  DEBUG ("snmp plugin: csnmp_read_host (%s) started at %u;", host->name,
      (unsigned int) time_start);

  if (host->sess_handle == NULL)
    csnmp_host_open_session (host);

  if (host->sess_handle == NULL)
    return (-1);

  success = 0;
  for (i = 0; i < host->data_list_len; i++)
  {
    data_definition_t *data = host->data_list[i];

    if (data->is_table)
      status = csnmp_read_table (host, data);
    else
      status = csnmp_read_value (host, data);

    if (status == 0)
      success++;
  }

  time_end = time (NULL);
  DEBUG ("snmp plugin: csnmp_read_host (%s) finished at %u;", host->name,
      (unsigned int) time_end);
  if ((uint32_t) (time_end - time_start) > host->interval)
  {
    WARNING ("snmp plugin: Host `%s' should be queried every %"PRIu32
        " seconds, but reading all values takes %u seconds.",
        host->name, host->interval, (unsigned int) (time_end - time_start));
  }

  if (success == 0)
    return (-1);

  return (0);
}