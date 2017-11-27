static int ir_init (void)
{
  memset (&rth, '\0', sizeof (rth));

  if (rtnl_open (&rth, 0) != 0)
  {
    ERROR ("netlink plugin: ir_init: rtnl_open failed.");
    return (-1);
  }

  return (0);
}