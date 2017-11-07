int mutt_is_multipart_signed (BODY *b)
{
  char *p;

  if (!b || b->type != TYPEMULTIPART ||
      !b->subtype || ascii_strcasecmp (b->subtype, "signed") ||
      !(p = mutt_get_parameter ("protocol", b->parameter)) ||
      (ascii_strcasecmp (p, "application/pgp-signature")
      && ascii_strcasecmp (p, "multipart/mixed")))
    return 0;

  return PGPSIGN;
}