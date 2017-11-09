static int crypt_mod_pgp_check_traditional (FILE *fp, BODY *b, int just_one)
{
  return pgp_check_traditional (fp, b, just_one);
}