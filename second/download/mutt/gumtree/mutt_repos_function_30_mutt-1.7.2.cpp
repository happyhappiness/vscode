int crypt_pgp_check_traditional (FILE *fp, BODY *b, int tagged_only)
{
  if (CRYPT_MOD_CALL_CHECK (PGP, pgp_check_traditional))
    return (CRYPT_MOD_CALL (PGP, pgp_check_traditional)) (fp, b, tagged_only);

  return 0;
}