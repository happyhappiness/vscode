int mutt_is_text_part (BODY *b)
{
  int t = b->type;
  char *s = b->subtype;
  
  if ((WithCrypto & APPLICATION_PGP) && mutt_is_application_pgp (b))
    return 0;

  if (t == TYPETEXT)
    return 1;

  if (t == TYPEMESSAGE)
  {
    if (!ascii_strcasecmp ("delivery-status", s))
      return 1;
  }

  if ((WithCrypto & APPLICATION_PGP) && t == TYPEAPPLICATION)
  {
    if (!ascii_strcasecmp ("pgp-keys", s))
      return 1;
  }

  return 0;
}