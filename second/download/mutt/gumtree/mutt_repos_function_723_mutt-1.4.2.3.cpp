int mutt_is_subscribed_list (ADDRESS *addr)
{
  return _mutt_is_mail_list (addr, SubscribedLists);
}