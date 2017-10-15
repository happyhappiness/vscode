void mutt_ts_icon(char *str)
{
  /* If empty, do not set.  To clear, use a single space. */
  if (str == NULL || *str == '\0')
    return;

  /* icon setting is not supported in terminfo, so hardcode the escape - yuck */
  fprintf(stderr, "\033]1;%s\007", str);
}