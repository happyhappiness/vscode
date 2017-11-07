BODY *pgp_gpgme_sign_message (BODY *a)
{
  return sign_message (a, 0);
}