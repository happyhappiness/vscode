static int conn_read (void)
{
  int status;
  char *buffer;
  size_t buffer_len;;

  struct xinpgen *in_orig;
  struct xinpgen *in_ptr;

  conn_reset_port_entry ();

  buffer_len = 0;
  status = sysctlbyname ("net.inet.tcp.pcblist", NULL, &buffer_len, 0, 0);
  if (status < 0)
  {
    ERROR ("tcpconns plugin: sysctlbyname failed.");
    return (-1);
  }

  buffer = (char *) malloc (buffer_len);
  if (buffer == NULL)
  {
    ERROR ("tcpconns plugin: malloc failed.");
    return (-1);
  }

  status = sysctlbyname ("net.inet.tcp.pcblist", buffer, &buffer_len, 0, 0);
  if (status < 0)
  {
    ERROR ("tcpconns plugin: sysctlbyname failed.");
    sfree (buffer);
    return (-1);
  }

  if (buffer_len <= sizeof (struct xinpgen))
  {
    ERROR ("tcpconns plugin: (buffer_len <= sizeof (struct xinpgen))");
    sfree (buffer);
    return (-1);
  }

  in_orig = (struct xinpgen *) buffer;
  for (in_ptr = (struct xinpgen *) (((char *) in_orig) + in_orig->xig_len);
      in_ptr->xig_len > sizeof (struct xinpgen);
      in_ptr = (struct xinpgen *) (((char *) in_ptr) + in_ptr->xig_len))
  {
    struct tcpcb *tp = &((struct xtcpcb *) in_ptr)->xt_tp;
    struct inpcb *inp = &((struct xtcpcb *) in_ptr)->xt_inp;
    struct xsocket *so = &((struct xtcpcb *) in_ptr)->xt_socket;

    /* Ignore non-TCP sockets */
    if (so->xso_protocol != IPPROTO_TCP)
      continue;

    /* Ignore PCBs which were freed during copyout. */
    if (inp->inp_gencnt > in_orig->xig_gen)
      continue;

    if (((inp->inp_vflag & INP_IPV4) == 0)
	&& ((inp->inp_vflag & INP_IPV6) == 0))
      continue;

    conn_handle_ports (inp->inp_lport, inp->inp_fport, tp->t_state);
  } /* for (in_ptr) */

  in_orig = NULL;
  in_ptr = NULL;
  sfree (buffer);

  conn_submit_all ();

  return (0);
}