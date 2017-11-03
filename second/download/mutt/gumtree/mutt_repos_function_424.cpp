static char *openssl_md_to_smime_micalg(char *md)
{
  char *micalg;
  size_t l;

  if (!md)
    return 0;

  if (mutt_strncasecmp ("sha", md, 3) == 0)
  {
    l = strlen (md) + 2;
    micalg = (char *)safe_malloc (l);
    snprintf (micalg, l, "sha-%s", md +3);
  }
  else
  {
    micalg = safe_strdup (md);
  }

  return micalg;
}