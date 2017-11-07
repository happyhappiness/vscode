int mutt_is_mail_list (ADDRESS *addr)
{
  if (!mutt_match_rx_list (addr->mailbox, UnMailLists))
    return mutt_match_rx_list (addr->mailbox, MailLists);
  return 0;
}