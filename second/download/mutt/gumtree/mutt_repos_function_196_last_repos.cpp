void mutt_remove_trailing_ws (char *s)
{
  char *p;
  
  for (p = s + mutt_strlen (s) - 1 ; p >= s && ISSPACE (*p) ; p--)
    *p = 0;
}