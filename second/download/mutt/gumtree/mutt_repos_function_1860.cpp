static void makedoc (FILE *in, FILE *out)
{
  char buffer[BUFFSIZE];
  char token[BUFFSIZE];
  char *p;
  int active = 0;
  int line = 0;
  int docstat = D_INIT;

  while ((fgets (buffer, sizeof (buffer), in)))
  {
    line++;
    if ((p = strchr (buffer, '\n')) == NULL)
    {
      fprintf (stderr, "%s: Line %d too long.  Ask a wizard to enlarge\n"
	               "%s: my buffer size.\n", Progname, line, Progname);
      exit (1);
    }
    else
      *p = '\0';

    if (!(p = get_token (token, sizeof (token), buffer)))
      continue;

    if (Debug)
    {
      fprintf (stderr, "%s: line %d.  first token: \"%s\".\n",
	       Progname, line, token);
    }
    
    if (!strcmp (token, "/*++*/"))
      active = 1;
    else if (!strcmp (token, "/*--*/"))
    {
      docstat = flush_doc (docstat, out);
      active = 0;
    }
    else if (active && (!strcmp (token, "/**") || !strcmp (token, "**")))
      docstat = handle_docline (p, out, docstat);
    else if (active && !strcmp (token, "{"))
    {
      docstat = flush_doc (docstat, out);
      handle_confline (p, out);
    }
  }
  flush_doc (docstat, out);
  fputs ("\n", out);
}