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

	case SP_END_FT: docstat &= ~(D_EM|D_BF|D_TT); break;
	case SP_START_BF: docstat |= D_BF; break;
	case SP_START_EM: docstat |= D_EM; break;
        case SP_START_TT: docstat |= D_TT; break;
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
	  if (docstat & D_IL)
	    fputs ("- ", out);
	  Continuation = 0;
	  break;
	}
	case SP_END_DL:
	{
	  Continuation = 0;
	  docstat &= ~D_DL;
	  break;
	}
	case SP_START_IL:
	{
	  docstat |= D_IL;
	  break;
	}
	case SP_END_IL:
	{
	  Continuation = 0;
	  docstat &= ~D_IL;
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
	  docstat &= ~(D_EM|D_BF|D_TT);
	  break;
	}
	case SP_START_BF: 
	{
	  fputs ("\\fB", out);
	  docstat |= D_BF;
	  docstat &= ~(D_EM|D_TT);
	  break;
	}
	case SP_START_EM:
	{
	  fputs ("\\fI", out);
	  docstat |= D_EM;
	  docstat &= ~(D_BF|D_TT);
	  break;
	}
        case SP_START_TT:
	{
	  fputs ("\\fC", out);
	  docstat |= D_TT;
	  docstat &= ~(D_BF|D_EM);
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
	  fputs ("\n.IP\n.EX\n", out);
	  docstat |= D_TAB | D_NL;
	  break;
	}
	case SP_END_TAB:
	{
	  fputs ("\n.EE\n", out);
	  docstat &= ~D_TAB;
	  docstat |= D_NL;
	  break;
	}
	case SP_START_DL:
	{
	  fputs (".RS\n.PD 0\n", out);
	  docstat |= D_DL;
	  break;
	}
	case SP_DT:
	{
	  fputs (".TP\n", out);
	  break;
	}
	case SP_DD:
	{
	  if (docstat & D_IL)
	    fputs (".TP\n\\(hy ", out);
	  else
	    fputs ("\n", out);
	  break;
	}
	case SP_END_DL:
	{
	  fputs (".RE\n.PD 1", out);
	  docstat &= ~D_DL;
	  break;
	}
	case SP_START_IL:
	{
	  fputs (".RS\n.PD 0\n", out);
	  docstat |= D_IL;
	  break;
	}
	case SP_END_IL:
	{
	  fputs (".RE\n.PD 1", out);
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
              else if (*str == '-')
                fputs ("\\-", out);
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
	  if (docstat & D_EM) fputs ("</emphasis>", out);
	  if (docstat & D_BF) fputs ("</emphasis>", out);
          if (docstat & D_TT) fputs ("</literal>", out);
	  docstat &= ~(D_EM|D_BF|D_TT);
	  break;
	}
	case SP_START_BF: 
	{
	  fputs ("<emphasis role=\"bold\">", out);
	  docstat |= D_BF;
	  docstat &= ~(D_EM|D_TT);
	  break;
	}
	case SP_START_EM:
	{
	  fputs ("<emphasis>", out);
	  docstat |= D_EM;
	  docstat &= ~(D_BF|D_TT);
	  break;
	}
        case SP_START_TT:
	{
	  fputs ("<literal>", out);
	  docstat |= D_TT;
	  docstat &= ~(D_BF|D_EM);
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
	  if (docstat & D_PA)
	    fputs("</para>\n", out);
	  fputs ("<para>\n", out);

	  docstat |= D_NP;
	  docstat |= D_PA;

	  break;
	}
        case SP_END_PAR:
        {
	  fputs ("</para>\n", out);
	  docstat &= ~D_PA;
	  break;
        }
	case SP_START_TAB:
	{
	  if (docstat & D_PA)
	  {
	    fputs ("\n</para>\n", out);
	    docstat &= ~D_PA;
	  }
	  fputs ("\n<screen>\n", out);
	  docstat |= D_TAB | D_NL;
	  break;
	}
	case SP_END_TAB:
	{
	  fputs ("</screen>", out);
	  docstat &= ~D_TAB;
	  docstat |= D_NL;
	  break;
	}
	case SP_START_DL:
	{
	  if (docstat & D_PA)
	  {
	    fputs ("\n</para>\n", out);
	    docstat &= ~D_PA;
	  }
	  fputs ("\n<informaltable>\n<tgroup cols=\"2\">\n<tbody>\n", out);
	  docstat |= D_DL;
	  break;
	}
	case SP_DT:
	{
	  fputs ("<row><entry>", out);
	  break;
	}
	case SP_DD:
	{
	  docstat |= D_DD;
	  if (docstat & D_DL)
	    fputs("</entry><entry>", out);
	  else
	    fputs ("<listitem><para>", out);
	  break;
	}
        case SP_END_DD:
        {
	  if (docstat & D_DL)
	    fputs ("</entry></row>\n", out);
	  else
	    fputs ("</para></listitem>", out);
	  docstat &= ~D_DD;
	  break;
        }
	case SP_END_DL:
	{
	  fputs ("</entry></row></tbody></tgroup></informaltable>\n", out);
	  docstat &= ~(D_DD|D_DL);
	  break;
	}
	case SP_START_IL:
	{
	  if (docstat & D_PA)
	  {
	    fputs ("\n</para>\n", out);
	    docstat &= ~D_PA;
	  }
	  fputs ("\n<itemizedlist>\n", out);
	  docstat |= D_IL;
	  break;
	}
	case SP_END_IL:
	{
	  fputs ("</para></listitem></itemizedlist>\n", out);
	  docstat &= ~(D_DD|D_DL);
	  break;
	}
        case SP_END_SECT:
        {
	  fputs ("</sect2>", out);
	  break;
        }
	case SP_STR:
	{
	  if (docstat & D_TAB)
	    sgml_fputs (str, out);
	  else
	  {
	    while (*str)
	    {
	      for (; *str; str++)
	      {
	        if (!strncmp (str, "``", 2))
	        {
		  fputs ("<quote>", out);
		  str++;
	        }
	        else if (!strncmp (str, "''", 2))
	        {
		  fputs ("</quote>", out);
		  str++;
	        }
	        else
		  sgml_fputc (*str, out);
	      }
	    }
	  }
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