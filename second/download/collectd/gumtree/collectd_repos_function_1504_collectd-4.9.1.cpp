static int cr_read (user_data_t *user_data) /* {{{ */
{
  int status;
  cr_data_t *rd;

  if (user_data == NULL)
    return (EINVAL);

  rd = user_data->data;
  if (rd == NULL)
    return (EINVAL);

  if (rd->connection == NULL)
  {
    rd->connection = ros_connect (rd->node, rd->service,
	rd->username, rd->password);
    if (rd->connection == NULL)
    {
      char errbuf[128];
      ERROR ("routeros plugin: ros_connect failed: %s",
	  sstrerror (errno, errbuf, sizeof (errbuf)));
      return (-1);
    }
  }
  assert (rd->connection != NULL);

  if (rd->collect_interface)
  {
    status = ros_interface (rd->connection, handle_interface,
	/* user data = */ rd);
    if (status != 0)
    {
      char errbuf[128];
      ERROR ("routeros plugin: ros_interface failed: %s",
	  sstrerror (status, errbuf, sizeof (errbuf)));
      ros_disconnect (rd->connection);
      rd->connection = NULL;
      return (-1);
    }
  }

  if (rd->collect_regtable)
  {
    status = ros_registration_table (rd->connection, handle_regtable,
	/* user data = */ rd);
    if (status != 0)
    {
      char errbuf[128];
      ERROR ("routeros plugin: ros_registration_table failed: %s",
	  sstrerror (status, errbuf, sizeof (errbuf)));
      ros_disconnect (rd->connection);
      rd->connection = NULL;
      return (-1);
    }
  }

  return (0);
}