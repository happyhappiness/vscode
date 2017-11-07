static char *get_token (char *d, size_t l, char *s)
{
  char *t;
  short is_quoted = 0;
  char *dd = d;

  if (Debug)
     fprintf (stderr, "%s: get_token called for `%s'.\n",
	      Progname, s);
  
  s = skip_ws (s);

  if (Debug > 1)
    fprintf (stderr, "%s: argument after skip_ws():  `%s'.\n",
	     Progname, s);

  if (!*s)
  {
    if (Debug)
      fprintf (stderr, "%s: no more tokens on this line.\n", Progname);
    return NULL;
  }

  if (strchr (single_char_tokens, *s))
  {
    if (Debug)
    {
      fprintf (stderr, "%s: found single character token `%c'.\n",
	       Progname, *s);
    }
    d[0] = *s++;
    d[1] = 0;
    return s;
  }

  if (*s == '"')
  {
    if (Debug)
    {
      fprintf (stderr, "%s: found quote character.\n", Progname);
    }
      
    s++;
    is_quoted = 1;
  }

  for (t = s; *t && --l > 0; t++)
  {
    if (*t == '\\' && !t[1])
      break;

    if (is_quoted && *t == '\\')
    {
      switch ((*d = *++t))
      {
	case 'n': *d = '\n'; break;
	case 't': *d = '\t'; break;
	case 'r': *d = '\r'; break;
	case 'a': *d = '\a'; break;
      }

      d++;
      continue;
    }

    if (is_quoted && *t == '"')
    {
      t++;
      break;
    }
    else if (!is_quoted && strchr (single_char_tokens, *t))
      break;
    else if (!is_quoted && isspace ((unsigned char) *t))
      break;
    else
      *d++ = *t;
  }

  *d = '\0';

  if (Debug)
  {
    fprintf (stderr, "%s: Got %stoken: `%s'.\n",
	     Progname, is_quoted ? "quoted " : "", dd);
    fprintf (stderr, "%s: Remainder: `%s'.\n",
	     Progname, t);
  }
  
  return t;
}