static int qos_filter (const struct sockaddr_nl *sa,
    struct nlmsghdr *nmh, void *args)
{
  struct tcmsg *msg;
  int msg_len;
  struct rtattr *attrs[TCA_MAX + 1];

  int wanted_ifindex = *((int *) args);

  const char *dev;

  /* char *type_instance; */
  char *tc_type;
  char tc_inst[DATA_MAX_NAME_LEN];

  if (nmh->nlmsg_type == RTM_NEWQDISC)
    tc_type = "qdisc";
  else if (nmh->nlmsg_type == RTM_NEWTCLASS)
    tc_type = "class";
  else if (nmh->nlmsg_type == RTM_NEWTFILTER)
    tc_type = "filter";
  else
  {
    ERROR ("netlink plugin: qos_filter: Don't know how to handle type %i.",
	nmh->nlmsg_type);
    return (-1);
  }

  msg = NLMSG_DATA (nmh);

  msg_len = nmh->nlmsg_len - sizeof (struct tcmsg);
  if (msg_len < 0)
  {
    ERROR ("netlink plugin: qos_filter: msg_len = %i < 0;", msg_len);
    return (-1);
  }

  if (msg->tcm_ifindex != wanted_ifindex)
  {
    DEBUG ("netlink plugin: qos_filter: Got %s for interface #%i, "
	"but expected #%i.",
	tc_type, msg->tcm_ifindex, wanted_ifindex);
    return (0);
  }

  if (msg->tcm_ifindex >= iflist_len)
  {
    ERROR ("netlink plugin: qos_filter: msg->tcm_ifindex = %i "
	">= iflist_len = %zu",
	msg->tcm_ifindex, iflist_len);
    return (-1);
  }

  dev = iflist[msg->tcm_ifindex];
  if (dev == NULL)
  {
    ERROR ("netlink plugin: qos_filter: iflist[%i] == NULL",
	msg->tcm_ifindex);
    return (-1);
  }

  memset (attrs, '\0', sizeof (attrs));
  if (parse_rtattr (attrs, TCA_MAX, TCA_RTA (msg), msg_len) != 0)
  {
    ERROR ("netlink plugin: qos_filter: parse_rtattr failed.");
    return (-1);
  }

  if (attrs[TCA_KIND] == NULL)
  {
    ERROR ("netlink plugin: qos_filter: attrs[TCA_KIND] == NULL");
    return (-1);
  }

  { /* The the ID */
    uint32_t numberic_id;

    numberic_id = msg->tcm_handle;
    if (strcmp (tc_type, "filter") == 0)
      numberic_id = msg->tcm_parent;

    ssnprintf (tc_inst, sizeof (tc_inst), "%s-%x:%x",
	(const char *) RTA_DATA (attrs[TCA_KIND]),
	numberic_id >> 16,
	numberic_id & 0x0000FFFF);
  }

  DEBUG ("netlink plugin: qos_filter: got %s for %s (%i).",
      tc_type, dev, msg->tcm_ifindex);
  
  if (check_ignorelist (dev, tc_type, tc_inst))
    return (0);

#if HAVE_TCA_STATS2
  if (attrs[TCA_STATS2])
  {
    struct rtattr *attrs_stats[TCA_STATS_MAX + 1];

    memset (attrs_stats, '\0', sizeof (attrs_stats));
    parse_rtattr_nested (attrs_stats, TCA_STATS_MAX, attrs[TCA_STATS2]);

    if (attrs_stats[TCA_STATS_BASIC])
    {
      struct gnet_stats_basic bs;
      char type_instance[DATA_MAX_NAME_LEN];

      ssnprintf (type_instance, sizeof (type_instance), "%s-%s",
	  tc_type, tc_inst);

      memset (&bs, '\0', sizeof (bs));
      memcpy (&bs, RTA_DATA (attrs_stats[TCA_STATS_BASIC]),
	  MIN (RTA_PAYLOAD (attrs_stats[TCA_STATS_BASIC]), sizeof(bs)));

      submit_one (dev, "ipt_bytes", type_instance, bs.bytes);
      submit_one (dev, "ipt_packets", type_instance, bs.packets);
    }
  }
#endif /* TCA_STATS2 */
#if HAVE_TCA_STATS && HAVE_TCA_STATS2
  else
#endif
#if HAVE_TCA_STATS
  if (attrs[TCA_STATS] != NULL)
  {
    struct tc_stats ts;
    char type_instance[DATA_MAX_NAME_LEN];

    ssnprintf (type_instance, sizeof (type_instance), "%s-%s",
	tc_type, tc_inst);

    memset(&ts, '\0', sizeof (ts));
    memcpy(&ts, RTA_DATA (attrs[TCA_STATS]),
	MIN (RTA_PAYLOAD (attrs[TCA_STATS]), sizeof (ts)));

    submit_one (dev, "ipt_bytes", type_instance, ts.bytes);
    submit_one (dev, "ipt_packets", type_instance, ts.packets);
  }
#endif /* TCA_STATS */
#if HAVE_TCA_STATS || HAVE_TCA_STATS2
  else
#endif
  {
    DEBUG ("netlink plugin: qos_filter: Have neither TCA_STATS2 nor "
	"TCA_STATS.");
  }

  return (0);
}