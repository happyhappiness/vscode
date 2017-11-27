static int ir_read (void)
{
  struct ifinfomsg im;
  struct tcmsg tm;
  int ifindex;

  static const int type_id[] = { RTM_GETQDISC, RTM_GETTCLASS, RTM_GETTFILTER };
  static const char *type_name[] = { "qdisc", "class", "filter" };

  memset (&im, '\0', sizeof (im));
  im.ifi_type = AF_UNSPEC;

  if (rtnl_dump_request (&rth, RTM_GETLINK, &im, sizeof (im)) < 0)
  {
    ERROR ("netlink plugin: ir_read: rtnl_dump_request failed.");
    return (-1);
  }

  if (rtnl_dump_filter (&rth, link_filter, /* arg1 = */ NULL,
	NULL, NULL) != 0)
  {
    ERROR ("netlink plugin: ir_read: rtnl_dump_filter failed.");
    return (-1);
  }

  /* `link_filter' will update `iflist' which is used here to iterate over all
   * interfaces. */
  for (ifindex = 0; ifindex < iflist_len; ifindex++)
  {
    int type_index;

    if (iflist[ifindex] == NULL)
      continue;

    for (type_index = 0; type_index < STATIC_ARRAY_SIZE (type_id); type_index++)
    {
      if (check_ignorelist (iflist[ifindex], type_name[type_index], NULL))
      {
	DEBUG ("netlink plugin: ir_read: check_ignorelist (%s, %s, (nil)) "
	    "== TRUE", iflist[ifindex], type_name[type_index]);
	continue;
      }

      DEBUG ("netlink plugin: ir_read: querying %s from %s (%i).",
	  type_name[type_index], iflist[ifindex], ifindex);

      memset (&tm, '\0', sizeof (tm));
      tm.tcm_family = AF_UNSPEC;
      tm.tcm_ifindex = ifindex;

      if (rtnl_dump_request (&rth, type_id[type_index], &tm, sizeof (tm)) < 0)
      {
	ERROR ("netlink plugin: ir_read: rtnl_dump_request failed.");
	continue;
      }

      if (rtnl_dump_filter (&rth, qos_filter, (void *) &ifindex,
	    NULL, NULL) != 0)
      {
	ERROR ("netlink plugin: ir_read: rtnl_dump_filter failed.");
	continue;
      }
    } /* for (type_index) */
  } /* for (if_index) */

  return (0);
}