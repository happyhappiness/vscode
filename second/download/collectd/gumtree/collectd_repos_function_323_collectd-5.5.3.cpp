static int qos_filter_cb (const struct nlmsghdr *nlh, void *args)
{
  struct tcmsg *tm = mnl_nlmsg_get_payload (nlh);
  struct nlattr *attr;

  int wanted_ifindex = *((int *) args);

  const char *dev;
  const char *kind = NULL;

  /* char *type_instance; */
  char *tc_type;
  char tc_inst[DATA_MAX_NAME_LEN];

  _Bool stats_submitted = 0;

  if (nlh->nlmsg_type == RTM_NEWQDISC)
    tc_type = "qdisc";
  else if (nlh->nlmsg_type == RTM_NEWTCLASS)
    tc_type = "class";
  else if (nlh->nlmsg_type == RTM_NEWTFILTER)
    tc_type = "filter";
  else
  {
    ERROR ("netlink plugin: qos_filter_cb: Don't know how to handle type %i.",
        nlh->nlmsg_type);
    return MNL_CB_ERROR;
  }

  if (tm->tcm_ifindex != wanted_ifindex)
  {
    DEBUG ("netlink plugin: qos_filter_cb: Got %s for interface #%i, "
        "but expected #%i.",
        tc_type, tm->tcm_ifindex, wanted_ifindex);
    return MNL_CB_OK;
  }

  if ((tm->tcm_ifindex >= 0)
      && ((size_t) tm->tcm_ifindex >= iflist_len))
  {
    ERROR ("netlink plugin: qos_filter_cb: tm->tcm_ifindex = %i "
        ">= iflist_len = %zu",
        tm->tcm_ifindex, iflist_len);
    return MNL_CB_ERROR;
  }

  dev = iflist[tm->tcm_ifindex];
  if (dev == NULL)
  {
    ERROR ("netlink plugin: qos_filter_cb: iflist[%i] == NULL",
        tm->tcm_ifindex);
    return MNL_CB_ERROR;
  }

  mnl_attr_for_each (attr, nlh, sizeof (*tm))
  {
    if (mnl_attr_get_type (attr) != TCA_KIND)
      continue;

    if (mnl_attr_validate (attr, MNL_TYPE_STRING) < 0)
    {
      ERROR ("netlink plugin: qos_filter_cb: TCA_KIND mnl_attr_validate failed.");
      return MNL_CB_ERROR;
    }

    kind = mnl_attr_get_str (attr);
    break;
  }

  if (kind == NULL)
  {
    ERROR ("netlink plugin: qos_filter_cb: kind == NULL");
    return (-1);
  }

  { /* The ID */
    uint32_t numberic_id;

    numberic_id = tm->tcm_handle;
    if (strcmp (tc_type, "filter") == 0)
      numberic_id = tm->tcm_parent;

    ssnprintf (tc_inst, sizeof (tc_inst), "%s-%x:%x",
        kind,
        numberic_id >> 16,
        numberic_id & 0x0000FFFF);
  }

  DEBUG ("netlink plugin: qos_filter_cb: got %s for %s (%i).",
      tc_type, dev, tm->tcm_ifindex);

  if (check_ignorelist (dev, tc_type, tc_inst))
    return MNL_CB_OK;

#if HAVE_TCA_STATS2
  mnl_attr_for_each (attr, nlh, sizeof (*tm))
  {
    struct gnet_stats_basic *bs = NULL;

    if (mnl_attr_get_type (attr) != TCA_STATS2)
      continue;

    if (mnl_attr_validate (attr, MNL_TYPE_NESTED) < 0)
    {
      ERROR ("netlink plugin: qos_filter_cb: TCA_STATS2 mnl_attr_validate failed.");
      return MNL_CB_ERROR;
    }

    mnl_attr_parse_nested (attr, qos_attr_cb, &bs);

    if (bs != NULL)
    {
      char type_instance[DATA_MAX_NAME_LEN];

      stats_submitted = 1;

      ssnprintf (type_instance, sizeof (type_instance), "%s-%s",
          tc_type, tc_inst);

      submit_one (dev, "ipt_bytes", type_instance, bs->bytes);
      submit_one (dev, "ipt_packets", type_instance, bs->packets);
    }

    break;
  }
#endif /* TCA_STATS2 */

#if HAVE_TCA_STATS
  mnl_attr_for_each (attr, nlh, sizeof (*tm))
  {
    struct tc_stats *ts = NULL;

    if (mnl_attr_get_type (attr) != TCA_STATS)
      continue;

    if (mnl_attr_validate2 (attr, MNL_TYPE_UNSPEC, sizeof (*ts)) < 0)
    {
      ERROR ("netlink plugin: qos_filter_cb: TCA_STATS mnl_attr_validate2 failed.");
      return MNL_CB_ERROR;
    }
    ts = mnl_attr_get_payload (attr);

    if (!stats_submitted && ts != NULL)
    {
      char type_instance[DATA_MAX_NAME_LEN];

      ssnprintf (type_instance, sizeof (type_instance), "%s-%s",
          tc_type, tc_inst);

      submit_one (dev, "ipt_bytes", type_instance, ts->bytes);
      submit_one (dev, "ipt_packets", type_instance, ts->packets);
    }

    break;
  }

#endif /* TCA_STATS */

#if !(HAVE_TCA_STATS && HAVE_TCA_STATS2)
  DEBUG ("netlink plugin: qos_filter_cb: Have neither TCA_STATS2 nor "
      "TCA_STATS.");
#endif

  return MNL_CB_OK;
}