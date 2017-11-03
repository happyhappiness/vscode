int crypt_pgp_application_pgp_handler (BODY *m, STATE *s)
{
  if (CRYPT_MOD_CALL_CHECK (PGP, application_handler))
    return (CRYPT_MOD_CALL (PGP, application_handler)) (m, s);
  
  return -1;
}