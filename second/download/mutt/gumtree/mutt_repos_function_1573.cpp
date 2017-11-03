void crypt_opportunistic_encrypt(HEADER *msg)
{
  char *pgpkeylist = NULL;

  if (!WithCrypto)
    return;

  if (! (option (OPTCRYPTOPPORTUNISTICENCRYPT) && (msg->security & OPPENCRYPT)) )
    return;

  crypt_get_keys (msg, &pgpkeylist, 1);
  if (pgpkeylist != NULL )
  {
    msg->security |= ENCRYPT;
    FREE (&pgpkeylist);
  }
  else
  {
    msg->security &= ~ENCRYPT;
  }
}