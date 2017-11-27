static int csnmp_read_host (user_data_t *ud)
{
  host_definition_t *host;
  cdtime_t time_start;
  cdtime_t time_end;
  int status;
  int success;
  int i;

  host = ud->data;

  if (host->interval == 0)
    host->interval = plugin_get_interval ();

  time_start = cdtime ();

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

  time_end = cdtime ();
  if ((time_end - time_start) > host->interval)
  {
    WARNING ("snmp plugin: Host `%s' should be queried every %.3f "
        "seconds, but reading all values takes %.3f seconds.",
        host->name,
        CDTIME_T_TO_DOUBLE (host->interval),
        CDTIME_T_TO_DOUBLE (time_end - time_start));
  }

  if (success == 0)
    return (-1);

  return (0);
}