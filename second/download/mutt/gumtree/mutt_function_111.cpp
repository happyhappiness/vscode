void mutt_ts_status(char *str)
{
  /* If empty, do not set.  To clear, use a single space. */
  if (str == NULL || *str == '\0')
    return;
  fprintf(stderr, "%s%s%s", tsl, str, fsl);
}