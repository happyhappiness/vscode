static int mb_read_slave (mb_host_t *host, mb_slave_t *slave) /* {{{ */
{
  mb_data_t *data;
  int success;
  int status;

  if ((host == NULL) || (slave == NULL))
    return (EINVAL);

  success = 0;
  for (data = slave->collect; data != NULL; data = data->next)
  {
    status = mb_read_data (host, slave, data);
    if (status == 0)
      success++;
  }

  if (success == 0)
    return (-1);
  else
    return (0);
}