void crypt_pgp_set_sender (const char *sender)
{
  if (CRYPT_MOD_CALL_CHECK (PGP, set_sender))
    (CRYPT_MOD_CALL (PGP, set_sender)) (sender);
}