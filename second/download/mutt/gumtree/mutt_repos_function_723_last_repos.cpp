static int get_micalg (gpgme_ctx_t ctx, int use_smime, char *buf, size_t buflen)
{
  gpgme_sign_result_t result = NULL;
  const char *algorithm_name = NULL;

  if (buflen < 5)
    return -1;

  *buf = 0;
  result = gpgme_op_sign_result (ctx);
  if (result && result->signatures)
  {
    algorithm_name = gpgme_hash_algo_name (result->signatures->hash_algo);
    if (algorithm_name)
    {
      if (use_smime)
      {
        /* convert GPGME raw hash name to RFC 2633 format */
        snprintf (buf, buflen, "%s", algorithm_name);
        ascii_strlower (buf);
      } else {
        /* convert GPGME raw hash name to RFC 3156 format */
        snprintf (buf, buflen, "pgp-%s", algorithm_name);
        ascii_strlower (buf + 4);
      }
    }
  }

  return *buf? 0:-1;
}