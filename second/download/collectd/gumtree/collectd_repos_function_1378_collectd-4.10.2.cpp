static int mb_read (user_data_t *user_data) /* {{{ */
{
  mb_host_t *host;
  size_t i;
  int success;
  int status;

  if ((user_data == NULL) || (user_data->data == NULL))
    return (EINVAL);

  host = user_data->data;

  /* Clear the reconnect flag. */
  host->have_reconnected = 0;

  success = 0;
  for (i = 0; i < host->slaves_num; i++)
  {
    status = mb_read_slave (host, host->slaves + i);
    if (status == 0)
      success++;
  }

  if (success == 0)
    return (-1);
  else
    return (0);
}