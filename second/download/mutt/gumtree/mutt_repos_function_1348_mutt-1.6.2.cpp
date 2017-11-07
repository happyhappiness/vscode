char *mutt_get_parameter (const char *s, PARAMETER *p)
{
  for (; p; p = p->next)
    if (ascii_strcasecmp (s, p->attribute) == 0)
      return (p->value);

  return NULL;
}