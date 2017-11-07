static const char *crypt_keyid (crypt_key_t *k)
{
  const char *s = "????????";

  if (k->kobj && k->kobj->subkeys)
    {
      s = k->kobj->subkeys->keyid;
      if ((! option (OPTPGPLONGIDS)) && (strlen (s) == 16))
	/* Return only the short keyID.  */
	s += 8;
    }

  return s;
}