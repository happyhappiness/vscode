static int mutt_check_boundary (const char* boundary, BODY *b)
{
  char* p;

  if (b->parts && mutt_check_boundary (boundary, b->parts))
    return 1;

  if (b->next && mutt_check_boundary (boundary, b->next))
    return 1;

  if ((p = mutt_get_parameter ("boundary", b->parameter))
      && !ascii_strcmp (p, boundary))
    return 1;
  return 0;
}