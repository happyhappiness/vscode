int mutt_is_list_recipient (int alladdr, ADDRESS *a1, ADDRESS *a2)
{
  for (; a1 ; a1 = a1->next)
    if (alladdr ^ mutt_is_subscribed_list (a1))
      return (! alladdr);
  for (; a2 ; a2 = a2->next)
    if (alladdr ^ mutt_is_subscribed_list (a2))
      return (! alladdr);
  return alladdr;
}