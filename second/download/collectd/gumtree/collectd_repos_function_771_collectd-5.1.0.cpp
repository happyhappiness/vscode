static int conn_read (void)
{
  struct inpcbtable table;
  struct inpcb *head;
  struct inpcb *next;
  struct inpcb inpcb;
  struct tcpcb tcpcb;
  int status;

  conn_reset_port_entry ();

  /* Read the pcbtable from the kernel */
  status = kread (inpcbtable_off, &table, sizeof (table));
  if (status != 0)
    return (-1);

  /* Get the `head' pcb */
  head = (struct inpcb *) &(inpcbtable_ptr->inpt_queue);
  /* Get the first pcb */
  next = (struct inpcb *)CIRCLEQ_FIRST (&table.inpt_queue);

  while (next != head)
  {
    /* Read the pcb pointed to by `next' into `inpcb' */
    kread ((u_long) next, &inpcb, sizeof (inpcb));

    /* Advance `next' */
    next = (struct inpcb *)CIRCLEQ_NEXT (&inpcb, inp_queue);

    /* Ignore sockets, that are not connected. */
#ifdef __NetBSD__
    if (inpcb.inp_af == AF_INET6)
      continue; /* XXX see netbsd/src/usr.bin/netstat/inet6.c */
#else
    if (!(inpcb.inp_flags & INP_IPV6)
	&& (inet_lnaof(inpcb.inp_laddr) == INADDR_ANY))
      continue;
    if ((inpcb.inp_flags & INP_IPV6)
	&& IN6_IS_ADDR_UNSPECIFIED (&inpcb.inp_laddr6))
      continue;
#endif

    kread ((u_long) inpcb.inp_ppcb, &tcpcb, sizeof (tcpcb));
    conn_handle_ports (ntohs(inpcb.inp_lport), ntohs(inpcb.inp_fport), tcpcb.t_state);
  } /* while (next != head) */

  conn_submit_all ();

  return (0);
}