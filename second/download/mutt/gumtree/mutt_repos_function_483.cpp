void mutt_unget_string (char *s)
{
  char *p = s + mutt_strlen (s) - 1;

  while (p >= s)
  {
    mutt_unget_event ((unsigned char)*p--, 0);
  }
}