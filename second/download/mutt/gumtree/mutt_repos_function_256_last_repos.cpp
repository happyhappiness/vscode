static int strict_cmp_lists (const LIST *a, const LIST *b)
{
  while (a && b)
  {
    if (mutt_strcmp (a->data, b->data))
      return (0);

    a = a->next;
    b = b->next;
  }
  if (a || b)
    return (0);

  return (1);
}