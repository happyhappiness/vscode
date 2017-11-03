void crypt_pgp_invoke_getkeys (ADDRESS *addr)
{
  if (CRYPT_MOD_CALL_CHECK (PGP, pgp_invoke_getkeys))
    (CRYPT_MOD_CALL (PGP, pgp_invoke_getkeys)) (addr);
}