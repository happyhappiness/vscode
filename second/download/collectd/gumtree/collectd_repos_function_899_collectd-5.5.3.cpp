static int conn_read (void)
{
  int status;

  conn_reset_port_entry ();

  if (linux_source == SRC_NETLINK)
  {
    status = conn_read_netlink ();
  }
  else if (linux_source == SRC_PROC)
  {
    int errors_num = 0;

    if (conn_read_file ("/proc/net/tcp") != 0)
      errors_num++;
    if (conn_read_file ("/proc/net/tcp6") != 0)
      errors_num++;

    if (errors_num < 2)
      status = 0;
    else
      status = ENOENT;
  }
  else /* if (linux_source == SRC_DUNNO) */
  {
    /* Try to use netlink for getting this data, it is _much_ faster on systems
     * with a large amount of connections. */
    status = conn_read_netlink ();
    if (status == 0)
    {
      INFO ("tcpconns plugin: Reading from netlink succeeded. "
	  "Will use the netlink method from now on.");
      linux_source = SRC_NETLINK;
    }
    else
    {
      INFO ("tcpconns plugin: Reading from netlink failed. "
	  "Will read from /proc from now on.");
      linux_source = SRC_PROC;

      /* return success here to avoid the "plugin failed" message. */
      return (0);
    }
  }

  if (status == 0)
    conn_submit_all ();
  else
    return (status);

  return (0);
}