static void free_recipient_set (gpgme_key_t **p_rset)
{
  gpgme_key_t *rset, k;

  if (!p_rset)
    return;

  rset = *p_rset;
  if (!rset)
    return;

  while (*rset)
  {
    k = *rset;
    gpgme_key_unref (k);
    rset++;
  }

  FREE (p_rset);	/* __FREE_CHECKED__ */
}