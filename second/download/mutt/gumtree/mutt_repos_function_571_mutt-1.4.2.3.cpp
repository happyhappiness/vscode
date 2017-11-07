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
      *ch++ = 0;
      SKIPWS (ch);
      break;
    }
  }
  mutt_remove_trailing_ws (s);
  return ch;
}