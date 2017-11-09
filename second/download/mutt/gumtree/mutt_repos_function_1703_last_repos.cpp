static int addresses_use_unicode(const ADDRESS* a)
{
  while (a)
  {
    if(a->mailbox && !a->group && address_uses_unicode(a->mailbox))
      return 1;
    a = a->next;
  }
  return 0;
}