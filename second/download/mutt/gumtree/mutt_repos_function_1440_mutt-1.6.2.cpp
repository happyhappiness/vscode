static int crypt_mod_pgp_check_traditional (FILE *fp, BODY *b, int tagged_only)
{
  return pgp_gpgme_check_traditional (fp, b, tagged_only);
}