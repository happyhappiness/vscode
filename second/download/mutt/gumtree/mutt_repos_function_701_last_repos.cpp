static const char *crypt_short_keyid (crypt_key_t *k)
{
  const char *s = "????????";

  if (k->kobj && k->kobj->subkeys)
    {
      s = k->kobj->subkeys->keyid;
      if (strlen (s) == 16)
        s += 8;
    }

  return s;
}