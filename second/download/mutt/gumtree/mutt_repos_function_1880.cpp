static int handle_docline (char *l, FILE *out, int docstat)
{
  char buff[BUFFSIZE];
  char *s, *d;
  l = skip_ws (l);

  if (Debug)
    fprintf (stderr, "%s: handle_docline `%s'\n", Progname, l);
  
  if (!strncmp (l, ".pp", 3))
    return print_it (SP_NEWPAR, NULL, out, docstat);
  else if (!strncmp (l, ".ts", 3))
    return print_it (SP_START_TAB, NULL, out, docstat);
  else if (!strncmp (l, ".te", 3))
    return print_it (SP_END_TAB, NULL, out, docstat);
  else if (!strncmp (l, ".dl", 3))
    return print_it (SP_START_DL, NULL, out, docstat);
  else if (!strncmp (l, ".de", 3))
    return print_it (SP_END_DL, NULL, out, docstat);
  else if (!strncmp (l, ".il", 3))
    return print_it (SP_START_IL, NULL, out, docstat);
  else if (!strncmp (l, ".ie", 3))
    return print_it (SP_END_IL, NULL, out, docstat);
  else if (!strncmp (l, ". ", 2))
    *l = ' ';

  for (s = l, d = buff; *s; s++)
  {
    if (!strncmp (s, "\\(as", 4))
    {
      *d++ = '*';
      s += 3;
    }
    else if (!strncmp (s, "\\(rs", 4))
    {
      *d++ = '\\';
      s += 3;
    }
    else if (!strncmp (s, "\\fI", 3))
    {
      docstat = commit_buff (buff, &d, out, docstat);
      docstat = print_it (SP_START_EM, NULL, out, docstat);
      s += 2;
    }
    else if (!strncmp (s, "\\fB", 3))
    {
      docstat = commit_buff (buff, &d, out, docstat);
      docstat = print_it (SP_START_BF, NULL, out, docstat);
      s += 2;
    }
    else if (!strncmp (s, "\\fC", 3))
    {
      docstat = commit_buff (buff, &d, out, docstat);
      docstat = print_it (SP_START_TT, NULL, out, docstat);
      s += 2;
    }
    else if (!strncmp (s, "\\fP", 3))
    {
      docstat = commit_buff (buff, &d, out, docstat);
      docstat = print_it (SP_END_FT, NULL, out, docstat);
      s += 2;
    }
    else if (!strncmp (s, ".dt", 3))
    {
      if (docstat & D_DD)
      {
	docstat = commit_buff (buff, &d, out, docstat);
	docstat = print_it (SP_END_DD, NULL, out, docstat);
      }
      docstat = commit_buff (buff, &d, out, docstat);
      docstat = print_it (SP_DT, NULL, out, docstat);
      s += 3;
    }
    else if (!strncmp (s, ".dd", 3))
    {
      if ((docstat & D_IL) && (docstat & D_DD))
      {
	docstat = commit_buff (buff, &d, out, docstat);
	docstat = print_it (SP_END_DD, NULL, out, docstat);
      }
      docstat = commit_buff (buff, &d, out, docstat);
      docstat = print_it (SP_DD, NULL, out, docstat);
      s += 3;
    }
    else if (*s == '$')
    {
      int output_dollar = 0;
      char *ref;
      char save;

      ++s;
      if (*s == '$')
      {
	output_dollar = 1;
	++s;
      }
      if (*s == '$')
      {
	*d++ = '$';
      }
      else
      {
	ref = s;
	while (isalnum ((unsigned char) *s) || (*s && strchr("-_<>", *s)))
	  ++s;

	docstat = commit_buff (buff, &d, out, docstat);
	save = *s;
	*s = 0;
	print_ref (out, output_dollar, ref);
	*s = save;
	--s;
      }
    }
    else
      *d++ = *s;
  }

  docstat = commit_buff (buff, &d, out, docstat);
  return print_it (SP_NEWLINE, NULL, out, docstat);
}