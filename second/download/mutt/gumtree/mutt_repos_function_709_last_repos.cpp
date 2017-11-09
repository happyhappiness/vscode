static int crypt_id_is_strong (crypt_key_t *key)
{
  unsigned int is_strong = 0;

  if ((key->flags & KEYFLAG_ISX509))
    return 1;

  switch (key->validity)
    {
    case GPGME_VALIDITY_UNKNOWN:
    case GPGME_VALIDITY_UNDEFINED:
    case GPGME_VALIDITY_NEVER:
    case GPGME_VALIDITY_MARGINAL:
      is_strong = 0;
      break;

    case GPGME_VALIDITY_FULL:
    case GPGME_VALIDITY_ULTIMATE:
      is_strong = 1;
      break;
    }

  return is_strong;
}