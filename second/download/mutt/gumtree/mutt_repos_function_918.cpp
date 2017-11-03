static char *get_field (char *s)
{
  char *ch;

  if (!s)
    return NULL;

  while ((ch = strpbrk (s, ";\\")) != NULL)
  {
    if (*ch == '\\')
    {
      s = ch + 1;
      if (*s)
	s++;
    }
    else
    {
      *ch = 0;
      ch = skip_email_wsp(ch + 1);
      break;
    }
  }
  mutt_remove_trailing_ws (s);
  return ch;
}