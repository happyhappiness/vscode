int mutt_is_multipart_signed (BODY *b)
{
  char *p;

  if (!b || !(b->type == TYPEMULTIPART) ||
      !b->subtype || ascii_strcasecmp(b->subtype, "signed"))
    return 0;

  if (!(p = mutt_get_parameter("protocol", b->parameter)))
    return 0;

  if (!(ascii_strcasecmp (p, "multipart/mixed")))
    return SIGN;

  if ((WithCrypto & APPLICATION_PGP)
      && !(ascii_strcasecmp (p, "application/pgp-signature")))
    return PGPSIGN;
    
  if ((WithCrypto & APPLICATION_SMIME)
      && !(ascii_strcasecmp (p, "application/x-pkcs7-signature")))
    return SMIMESIGN;
  if ((WithCrypto & APPLICATION_SMIME)
      && !(ascii_strcasecmp (p, "application/pkcs7-signature")))
    return SMIMESIGN;

  return 0;
}