int mutt_is_valid_multipart_pgp_encrypted (BODY *b)
{
  if (! mutt_is_multipart_encrypted (b))
    return 0;

  b = b->parts;
  if (!b || b->type != TYPEAPPLICATION ||
      !b->subtype || ascii_strcasecmp (b->subtype, "pgp-encrypted"))
    return 0;

  b = b->next;
  if (!b || b->type != TYPEAPPLICATION ||
      !b->subtype || ascii_strcasecmp (b->subtype, "octet-stream"))
    return 0;

  return PGPENCRYPT;
}