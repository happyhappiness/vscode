int crypt_pgp_check_traditional (FILE *fp, BODY *b, int just_one)
{
  if (CRYPT_MOD_CALL_CHECK (PGP, pgp_check_traditional))
    return (CRYPT_MOD_CALL (PGP, pgp_check_traditional)) (fp, b, just_one);

  return 0;
}