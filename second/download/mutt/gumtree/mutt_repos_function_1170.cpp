static int user_in_addr (ADDRESS *a)
{
  for (; a; a = a->next)
    if (mutt_addr_is_user (a))
      return 1;
  return 0;
}