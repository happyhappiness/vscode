static int
smtp_rcpt_to (CONNECTION * conn, const ADDRESS * a)
{
  char buf[1024];
  int r;

  while (a)
  {
    /* weed out group mailboxes, since those are for display only */
    if (!a->mailbox || a->group)
    {
      a = a->next;
      continue;
    }
    if (mutt_bit_isset (Capabilities, DSN) && DsnNotify)
      snprintf (buf, sizeof (buf), "RCPT TO:<%s> NOTIFY=%s\r\n",
                a->mailbox, DsnNotify);
    else
      snprintf (buf, sizeof (buf), "RCPT TO:<%s>\r\n", a->mailbox);
    if (mutt_socket_write (conn, buf) == -1)
      return smtp_err_write;
    if ((r = smtp_get_resp (conn)))
      return r;
    a = a->next;
  }

  return 0;
}