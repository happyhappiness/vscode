static int ir_read (void)
{
  char buf[MNL_SOCKET_BUFFER_SIZE];
  struct nlmsghdr *nlh;
  struct rtgenmsg *rt;
  int ret;
  unsigned int seq, portid;

  size_t ifindex;

  static const int type_id[] = { RTM_GETQDISC, RTM_GETTCLASS, RTM_GETTFILTER };
  static const char *type_name[] = { "qdisc", "class", "filter" };

  portid = mnl_socket_get_portid (nl);

  nlh = mnl_nlmsg_put_header (buf);
  nlh->nlmsg_type = RTM_GETLINK;
  nlh->nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;
  nlh->nlmsg_seq = seq = time (NULL);
  rt = mnl_nlmsg_put_extra_header (nlh, sizeof (*rt));
  rt->rtgen_family = AF_PACKET;

  if (mnl_socket_sendto (nl, nlh, nlh->nlmsg_len) < 0)
  {
    ERROR ("netlink plugin: ir_read: rtnl_wilddump_request failed.");
    return (-1);
  }

  ret = mnl_socket_recvfrom (nl, buf, sizeof (buf));
  while (ret > 0)
  {
    ret = mnl_cb_run (buf, ret, seq, portid, link_filter_cb, NULL);
    if (ret <= MNL_CB_STOP)
      break;
    ret = mnl_socket_recvfrom (nl, buf, sizeof (buf));
  }
  if (ret < 0)
  {
    ERROR ("netlink plugin: ir_read: mnl_socket_recvfrom failed.");
    return (-1);
  }

  /* `link_filter_cb' will update `iflist' which is used here to iterate
   * over all interfaces. */
  for (ifindex = 1; ifindex < iflist_len; ifindex++)
  {
    struct tcmsg *tm;
    size_t type_index;

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

      DEBUG ("netlink plugin: ir_read: querying %s from %s (%zu).",
          type_name[type_index], iflist[ifindex], ifindex);

      nlh = mnl_nlmsg_put_header (buf);
      nlh->nlmsg_type = type_id[type_index];
      nlh->nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;
      nlh->nlmsg_seq = seq = time (NULL);
      tm = mnl_nlmsg_put_extra_header (nlh, sizeof (*tm));
      tm->tcm_family = AF_PACKET;
      tm->tcm_ifindex = ifindex;

      if (mnl_socket_sendto (nl, nlh, nlh->nlmsg_len) < 0)
      {
        ERROR ("netlink plugin: ir_read: mnl_socket_sendto failed.");
        continue;
      }

      ret = mnl_socket_recvfrom (nl, buf, sizeof (buf));
      while (ret > 0)
      {
        ret = mnl_cb_run (buf, ret, seq, portid, qos_filter_cb, &ifindex);
        if (ret <= MNL_CB_STOP)
          break;
        ret = mnl_socket_recvfrom (nl, buf, sizeof (buf));
      }
      if (ret < 0)
      {
        ERROR ("netlink plugin: ir_read:mnl_socket_recvfrom failed.");
        continue;
      }

    } /* for (type_index) */
  } /* for (if_index) */

  return (0);
}