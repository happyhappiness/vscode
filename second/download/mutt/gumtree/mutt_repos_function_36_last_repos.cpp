void crypt_pgp_invoke_import (const char *fname)
{
  if (CRYPT_MOD_CALL_CHECK (PGP, pgp_invoke_import))
    (CRYPT_MOD_CALL (PGP, pgp_invoke_import)) (fname);
}