static int strict_addrcmp (const ADDRESS *a, const ADDRESS *b)
{
  while (a && b)
  {
    if (mutt_strcmp (a->mailbox, b->mailbox) ||
	mutt_strcmp (a->personal, b->personal))
      return (0);

    a = a->next;
    b = b->next;
  }
  if (a || b)
    return (0);

  return (1);
}