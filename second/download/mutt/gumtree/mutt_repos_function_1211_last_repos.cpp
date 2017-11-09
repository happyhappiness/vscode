int mutt_is_subscribed_list (ADDRESS *addr)
{
  if (!mutt_match_rx_list (addr->mailbox, UnMailLists)
      && !mutt_match_rx_list (addr->mailbox, UnSubscribedLists))
    return mutt_match_rx_list (addr->mailbox, SubscribedLists);
  return 0;
}