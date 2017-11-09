static int strict_cmp_parameters (const PARAMETER *p1, const PARAMETER *p2)
{
  while (p1 && p2)
  {
    if (mutt_strcmp (p1->attribute, p2->attribute) ||
	mutt_strcmp (p1->value, p2->value))
      return (0);

    p1 = p1->next;
    p2 = p2->next;
  }
  if (p1 || p2)
    return (0);

  return (1);
}