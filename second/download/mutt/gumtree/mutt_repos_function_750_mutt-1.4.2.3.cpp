static int print_it (int special, char *str, FILE *out, int docstat)
{
  int onl = docstat & (D_NL|D_NP);
  
  docstat &= ~(D_NL|D_NP|D_INIT);

  switch (OutputFormat)
  {
    /* configuration file */
    case F_CONF:
    {
      switch (special)
      {
	static int Continuation = 0;

	case SP_END_FT: docstat &= ~(D_EM|D_BF); break;
	case SP_START_BF: docstat |= D_BF; break;
	case SP_START_EM: docstat |= D_EM; break;
	case SP_NEWLINE: 
	{
	  if (onl)
	    docstat |= onl;
	  else
	  {
	    fputs ("\n# ", out);
	    docstat |= D_NL;
	  }
	  if (docstat & D_DL)
	    ++ Continuation;
	  break;
	}
	case SP_NEWPAR:
	{
	  if (onl & D_NP)
	  {
	    docstat |= onl;
	    break;
	  }

	  if (!(onl & D_NL))
	    fputs ("\n# ", out);
	  fputs ("\n# ", out);
	  docstat |= D_NP;
	  break;
	}
	case SP_START_TAB: 
	{
	  if (!onl) 
	    fputs ("\n# ", out);
	  docstat |= D_TAB;
	  break;
	}
	case SP_END_TAB:
	{
	  docstat &= ~D_TAB;
	  docstat |= D_NL;
	  break;
	}
	case SP_START_DL:
	{
	  docstat |= D_DL;
	  break;
	}
	case SP_DT:
	{
	  Continuation = 0;
	  docstat |= D_DT;
	  break;
	}
	case SP_DD:
	{
	  Continuation = 0;
	  break;
	}
	case SP_END_DL:
	{
	  Continuation = 0;
	  docstat &= ~D_DL;
	  break;
	}
	case SP_STR:
	{
	  if (Continuation)
	  {
	    Continuation = 0;
	    fputs ("        ", out);
	  }
	  fputs (str, out);
	  if (docstat & D_DT)
	  { 
	    int i;

	    for (i = strlen (str) ; i < 8 ; i++)
	      putc (' ', out);
	    docstat &= ~D_DT;
	    docstat |= D_NL;
	  }
	  break;
	}
      }
      break;
    }

    /* manual page */
    case F_MAN:
    {
      switch (special)
      {
	case SP_END_FT: 
	{
	  fputs ("\\fP", out);
	  docstat &= ~(D_EM|D_BF);
	  break;
	}
	case SP_START_BF: 
	{
	  fputs ("\\fB", out);
	  docstat |= D_BF;
	  docstat &= ~D_EM;
	  break;
	}
	case SP_START_EM:
	{
	  fputs ("\\fI", out);
	  docstat |= D_EM;
	  docstat &= ~D_BF;
	  break;
	}
	case SP_NEWLINE:
	{
	  if (onl)
	    docstat |= onl;
	  else
	  {
	    fputc ('\n', out);
	    docstat |= D_NL;
	  }
	  break;
	}
	case SP_NEWPAR:
	{
	  if (onl & D_NP)
	  {
	    docstat |= onl;
	    break;
	  }

	  if (!(onl & D_NL))
	    fputc ('\n', out);
	  fputs (".IP\n", out);

	  docstat |= D_NP;
	  break;
	}
	case SP_START_TAB:
	{
	  fputs ("\n.IP\n.DS\n.sp\n.ft CR\n.nf\n", out);
	  docstat |= D_TAB | D_NL;
	  break;
	}
	case SP_END_TAB:
	{
	  fputs ("\n.fi\n.ec\n.ft P\n.sp\n", out);
	  docstat &= ~D_TAB;
	  docstat |= D_NL;
	  break;
	}
	case SP_START_DL:
	{
	  fputs ("\n.RS", out);
	  docstat |= D_DL;
	  break;
	}
	case SP_DT:
	{
	  fputs ("\n.IP ", out);
	  break;
	}
	case SP_DD:
	{
	  fputs ("\n", out);
	  break;
	}
	case SP_END_DL:
	{
	  fputs ("\n.RE", out);
	  docstat &= ~D_DL;
	  break;
	}
	case SP_STR:
	{
	  while (*str)
	  {
	    for (; *str; str++)
	    {
	      if (*str == '"')
		fputs ("\\(rq", out);
	      else if (*str == '\\')
		fputs ("\\\\", out);
	      else if (!strncmp (str, "``", 2))
	      {
		fputs ("\\(lq", out);
		str++;
	      }
	      else if (!strncmp (str, "''", 2))
	      {
		fputs ("\\(rq", out);
		str++;
	      }
	      else
		fputc (*str, out);
	    }
	  }
	  break;
	}
      }
      break;
    }

    /* SGML based manual */
    case F_SGML:
    {
      switch (special)
      {
	case SP_END_FT: 
	{
	  if (docstat & D_EM) fputs ("</em>", out);
	  if (docstat & D_BF) fputs ("</bf>", out);
	  docstat &= ~(D_EM|D_BF);
	  break;
	}
	case SP_START_BF: 
	{
	  fputs ("<bf>", out);
	  docstat |= D_BF;
	  docstat &= ~D_EM;
	  break;
	}
	case SP_START_EM:
	{
	  fputs ("<em>", out);
	  docstat |= D_EM;
	  docstat &= ~D_BF;
	  break;
	}
	case SP_NEWLINE:
	{
	  if (onl)
	    docstat |= onl;
	  else
	  {
	    fputc ('\n', out);
	    docstat |= D_NL;
	  }
	  break;
	}
	case SP_NEWPAR:
	{
	  if (onl & D_NP)
	  {
	    docstat |= onl;
	    break;
	  }

	  if (!(onl & D_NL))
	    fputc ('\n', out);
	  fputs ("<p>\n", out);

	  docstat |= D_NP;
	  break;
	}
	case SP_START_TAB:
	{
	  fputs ("\n<tscreen><verb>\n", out);
	  docstat |= D_TAB | D_NL;
	  break;
	}
	case SP_END_TAB:
	{
	  fputs ("\n</verb></tscreen>", out);
	  docstat &= ~D_TAB;
	  docstat |= D_NL;
	  break;
	}
	case SP_START_DL:
	{
	  fputs ("\n<descrip>\n", out);
	  docstat |= D_DL;
	  break;
	}
	case SP_DT:
	{
	  fputs ("<tag>", out);
	  break;
	}
	case SP_DD:
	{
	  fputs ("</tag>", out);
	  break;
	}
	case SP_END_DL:
	{
	  fputs ("</descrip>\n", out);
	  docstat &= ~D_DL;
	  break;
	}
	case SP_STR:
	{
	  if (docstat & D_TAB)
	    fputs (str, out);
	  else
	    sgml_fputs (str, out);
	  break;
	}
      }
      break;
    }
    /* make gcc happy (unreached) */
    default:
      break;
  }

  return docstat;
}