ADDRESS *alias_reverse_lookup (ADDRESS *a)
{
  if (!a || !a->mailbox)
      return NULL;
  
  return hash_find (ReverseAlias, a->mailbox);
}