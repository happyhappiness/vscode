static int ir_init (void)
{
  memset (&rth, '\0', sizeof (rth));

  if (rtnl_open (&rth, 0) != 0)
  {
    ERROR ("netlink plugin: ir_read: rtnl_open failed.");
    return (-1);
  }

  if (ll_init_map (&rth) != 0)
  {
    ERROR ("netlink plugin: ir_read: ll_init_map failed.");
    return (-1);
  }

  return (0);
}