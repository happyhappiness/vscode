int crypt_pgp_encrypted_handler (BODY *a, STATE *s)
{
  if (CRYPT_MOD_CALL_CHECK (PGP, encrypted_handler))
    return (CRYPT_MOD_CALL (PGP, encrypted_handler)) (a, s);
  
  return -1;
}