static int has_recips (ADDRESS *a)
{
  int c = 0;

  for ( ; a; a = a->next)
  {
    if (!a->mailbox || a->group)
      continue;
    c++;
  }
  return c;
}