static const char *crypt_long_keyid (crypt_key_t *k)
{
  const char *s = "????????????????";

  if (k->kobj && k->kobj->subkeys)
    {
      s = k->kobj->subkeys->keyid;
    }

  return s;
}