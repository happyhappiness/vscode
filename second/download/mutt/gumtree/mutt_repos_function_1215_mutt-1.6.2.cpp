char *mutt_get_body_charset (char *d, size_t dlen, BODY *b)
{
  char *p = NULL;

  if (b && b->type != TYPETEXT)
    return NULL;

  if (b)
    p = mutt_get_parameter ("charset", b->parameter);

  if (p)
    mutt_canonical_charset (d, dlen, NONULL(p));
  else
    strfcpy (d, "us-ascii", dlen);

  return d;
}