ADDRESS *rfc822_cpy_adr (ADDRESS *addr)
{
  ADDRESS *top = NULL, *last = NULL;
  
  for (; addr; addr = addr->next)
  {
    if (last)
    {
      last->next = rfc822_cpy_adr_real (addr);
      last = last->next;
    }
    else
      top = last = rfc822_cpy_adr_real (addr);
  }
  return top;
}