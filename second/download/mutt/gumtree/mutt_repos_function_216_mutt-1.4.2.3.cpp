int mutt_is_multipart_encrypted (BODY *b)
{
  char *p;
  
  if (!b || b->type != TYPEMULTIPART ||
      !b->subtype || ascii_strcasecmp (b->subtype, "encrypted") ||
      !(p = mutt_get_parameter ("protocol", b->parameter)) ||
      ascii_strcasecmp (p, "application/pgp-encrypted"))
    return 0;
  
  return PGPENCRYPT;
}