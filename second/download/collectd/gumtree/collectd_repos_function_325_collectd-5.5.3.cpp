static int ir_init (void)
{
  nl = mnl_socket_open (NETLINK_ROUTE);
  if (nl == NULL)
  {
    ERROR ("netlink plugin: ir_init: mnl_socket_open failed.");
    return (-1);
  }

  if (mnl_socket_bind (nl, 0, MNL_SOCKET_AUTOPID) < 0)
  {
    ERROR ("netlink plugin: ir_init: mnl_socket_bind failed.");
    return (-1);
  }

  return (0);
}