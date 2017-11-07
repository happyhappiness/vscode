static smime_key_t *smime_get_candidates(char *search, short public)
{
  char index_file[_POSIX_PATH_MAX];
  FILE *fp;
  char buf[LONG_STRING];
  smime_key_t *key, *results, **results_end;

  results = NULL;
  results_end = &results;

  snprintf(index_file, sizeof (index_file), "%s/.index",
    public ? NONULL(SmimeCertificates) : NONULL(SmimeKeys));

  if ((fp = safe_fopen (index_file, "r")) == NULL)
  {
    mutt_perror (index_file);
    return NULL;
  }

  while (fgets (buf, sizeof (buf), fp))
  {
    if ((! *search) || mutt_stristr (buf, search))
    {
      key = smime_parse_key (buf);
      if (key)
      {
        *results_end = key;
        results_end = &key->next;
      }
    }
  }

  safe_fclose (&fp);

  return results;
}