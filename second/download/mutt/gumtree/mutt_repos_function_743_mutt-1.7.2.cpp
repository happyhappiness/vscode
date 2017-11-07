static unsigned int
key_check_cap (gpgme_key_t key, key_cap_t cap)
{
  gpgme_subkey_t subkey = NULL;
  unsigned int ret = 0;

  switch (cap)
    {
    case KEY_CAP_CAN_ENCRYPT:
      if (! (ret = key->can_encrypt))
	for (subkey = key->subkeys; subkey; subkey = subkey->next)
	  if ((ret = subkey->can_encrypt))
	    break;
      break;
    case KEY_CAP_CAN_SIGN:
      if (! (ret = key->can_sign))
	for (subkey = key->subkeys; subkey; subkey = subkey->next)
	  if ((ret = subkey->can_sign))
	    break;
      break;
    case KEY_CAP_CAN_CERTIFY:
      if (! (ret = key->can_certify))
	for (subkey = key->subkeys; subkey; subkey = subkey->next)
	  if ((ret = subkey->can_certify))
	    break;
      break;
    }

  return ret;
}