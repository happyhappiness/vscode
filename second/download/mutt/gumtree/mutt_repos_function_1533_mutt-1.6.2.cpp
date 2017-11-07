int mutt_is_malformed_multipart_pgp_encrypted (BODY *b)
{
  if (!(WithCrypto & APPLICATION_PGP))
    return 0;

  if (!b || b->type != TYPEMULTIPART ||
      !b->subtype || ascii_strcasecmp (b->subtype, "mixed"))
    return 0;

  b = b->parts;
  if (!b || b->type != TYPETEXT ||
      !b->subtype || ascii_strcasecmp (b->subtype, "plain") ||
       b->length != 0)
    return 0;

  b = b->next;
  if (!b || b->type != TYPEAPPLICATION ||
      !b->subtype || ascii_strcasecmp (b->subtype, "pgp-encrypted"))
    return 0;

  b = b->next;
  if (!b || b->type != TYPEAPPLICATION ||
      !b->subtype || ascii_strcasecmp (b->subtype, "octet-stream"))
    return 0;

  b = b->next;
  if (b)
    return 0;

  return PGPENCRYPT;
}