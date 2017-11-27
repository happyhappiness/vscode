static int conn_read_netlink (void)
{
#if HAVE_STRUCT_LINUX_INET_DIAG_REQ
  int fd;
  struct inet_diag_msg *r;
  char buf[8192];

  /* If this fails, it's likely a permission problem. We'll fall back to
   * reading this information from files below. */
  fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_INET_DIAG);
  if (fd < 0)
  {
    ERROR ("tcpconns plugin: conn_read_netlink: socket(AF_NETLINK, SOCK_RAW, "
	"NETLINK_INET_DIAG) failed: %s",
	sstrerror (errno, buf, sizeof (buf)));
    return (-1);
  }

  struct sockaddr_nl nladdr = {
    .nl_family = AF_NETLINK
  };

  struct nlreq req = {
    .nlh.nlmsg_len = sizeof(req),
    .nlh.nlmsg_type = TCPDIAG_GETSOCK,
    /* NLM_F_ROOT: return the complete table instead of a single entry.
     * NLM_F_MATCH: return all entries matching criteria (not implemented)
     * NLM_F_REQUEST: must be set on all request messages */
    .nlh.nlmsg_flags = NLM_F_ROOT | NLM_F_MATCH | NLM_F_REQUEST,
    .nlh.nlmsg_pid = 0,
    /* The sequence_number is used to track our messages. Since netlink is not
     * reliable, we don't want to end up with a corrupt or incomplete old
     * message in case the system is/was out of memory. */
    .nlh.nlmsg_seq = ++sequence_number,
    .r.idiag_family = AF_INET,
    .r.idiag_states = 0xfff,
    .r.idiag_ext = 0
  };

  struct iovec iov = {
    .iov_base = &req,
    .iov_len = sizeof(req)
  };

  struct msghdr msg = {
    .msg_name = (void*)&nladdr,
    .msg_namelen = sizeof(nladdr),
    .msg_iov = &iov,
    .msg_iovlen = 1
  };

  if (sendmsg (fd, &msg, 0) < 0)
  {
    ERROR ("tcpconns plugin: conn_read_netlink: sendmsg(2) failed: %s",
	sstrerror (errno, buf, sizeof (buf)));
    close (fd);
    return (-1);
  }

  iov.iov_base = buf;
  iov.iov_len = sizeof(buf);

  while (1)
  {
    int status;
    struct nlmsghdr *h;

    memset(&msg, 0, sizeof(msg));
    msg.msg_name = (void*)&nladdr;
    msg.msg_namelen = sizeof(nladdr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    status = recvmsg(fd, (void *) &msg, /* flags = */ 0);
    if (status < 0)
    {
      if ((errno == EINTR) || (errno == EAGAIN))
        continue;

      ERROR ("tcpconns plugin: conn_read_netlink: recvmsg(2) failed: %s",
	  sstrerror (errno, buf, sizeof (buf)));
      close (fd);
      return (-1);
    }
    else if (status == 0)
    {
      close (fd);
      DEBUG ("tcpconns plugin: conn_read_netlink: Unexpected zero-sized "
	  "reply from netlink socket.");
      return (0);
    }

    h = (struct nlmsghdr*)buf;
    while (NLMSG_OK(h, status))
    {
      if (h->nlmsg_seq != sequence_number)
      {
	h = NLMSG_NEXT(h, status);
	continue;
      }

      if (h->nlmsg_type == NLMSG_DONE)
      {
	close (fd);
	return (0);
      }
      else if (h->nlmsg_type == NLMSG_ERROR)
      {
	struct nlmsgerr *msg_error;

	msg_error = NLMSG_DATA(h);
	WARNING ("tcpconns plugin: conn_read_netlink: Received error %i.",
	    msg_error->error);

	close (fd);
	return (1);
      }

      r = NLMSG_DATA(h);

      /* This code does not (need to) distinguish between IPv4 and IPv6. */
      conn_handle_ports (ntohs(r->id.idiag_sport),
	  ntohs(r->id.idiag_dport),
	  r->idiag_state);

      h = NLMSG_NEXT(h, status);
    } /* while (NLMSG_OK) */
  } /* while (1) */

  /* Not reached because the while() loop above handles the exit condition. */
  return (0);
#else
  return (1);
#endif /* HAVE_STRUCT_LINUX_INET_DIAG_REQ */
}