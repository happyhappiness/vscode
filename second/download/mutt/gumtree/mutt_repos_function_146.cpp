static int match_user (int alladdr, ADDRESS *a1, ADDRESS *a2)
{
  for (; a1 ; a1 = a1->next)
    if (alladdr ^ mutt_addr_is_user (a1))
      return (! alladdr);
  for (; a2 ; a2 = a2->next)
    if (alladdr ^ mutt_addr_is_user (a2))
      return (! alladdr);
  return alladdr;
}