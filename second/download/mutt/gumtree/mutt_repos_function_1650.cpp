int mutt_extract_token (BUFFER *dest, BUFFER *tok, int flags)
{
  char		ch;
  char		qc = 0; /* quote char */
  char		*pc;

  /* reset the destination pointer to the beginning of the buffer */
  dest->dptr = dest->data;

  SKIPWS (tok->dptr);
  while ((ch = *tok->dptr))
  {
    if (!qc)
    {
      if ((ISSPACE (ch) && !(flags & MUTT_TOKEN_SPACE)) ||
	  (ch == '#' && !(flags & MUTT_TOKEN_COMMENT)) ||
	  (ch == '=' && (flags & MUTT_TOKEN_EQUAL)) ||
	  (ch == ';' && !(flags & MUTT_TOKEN_SEMICOLON)) ||
	  ((flags & MUTT_TOKEN_PATTERN) && strchr ("~%=!|", ch)))
	break;
    }

    tok->dptr++;

    if (ch == qc)
      qc = 0; /* end of quote */
    else if (!qc && (ch == '\'' || ch == '"') && !(flags & MUTT_TOKEN_QUOTE))
      qc = ch;
    else if (ch == '\\' && qc != '\'')
    {
	if (!*tok->dptr)
	    return -1; /* premature end of token */
      switch (ch = *tok->dptr++)
      {
	case 'c':
	case 'C':
	    if (!*tok->dptr)
		return -1; /* premature end of token */
	  mutt_buffer_addch (dest, (toupper ((unsigned char) *tok->dptr)
                                    - '@') & 0x7f);
	  tok->dptr++;
	  break;
	case 'r':
	  mutt_buffer_addch (dest, '\r');
	  break;
	case 'n':
	  mutt_buffer_addch (dest, '\n');
	  break;
	case 't':
	  mutt_buffer_addch (dest, '\t');
	  break;
	case 'f':
	  mutt_buffer_addch (dest, '\f');
	  break;
	case 'e':
	  mutt_buffer_addch (dest, '\033');
	  break;
	default:
	  if (isdigit ((unsigned char) ch) &&
	      isdigit ((unsigned char) *tok->dptr) &&
	      isdigit ((unsigned char) *(tok->dptr + 1)))
	  {

	    mutt_buffer_addch (dest, (ch << 6) + (*tok->dptr << 3) + *(tok->dptr + 1) - 3504);
	    tok->dptr += 2;
	  }
	  else
	    mutt_buffer_addch (dest, ch);
      }
    }
    else if (ch == '^' && (flags & MUTT_TOKEN_CONDENSE))
    {
	if (!*tok->dptr)
	    return -1; /* premature end of token */
      ch = *tok->dptr++;
      if (ch == '^')
	mutt_buffer_addch (dest, ch);
      else if (ch == '[')
	mutt_buffer_addch (dest, '\033');
      else if (isalpha ((unsigned char) ch))
	mutt_buffer_addch (dest, toupper ((unsigned char) ch) - '@');
      else
      {
	mutt_buffer_addch (dest, '^');
	mutt_buffer_addch (dest, ch);
      }
    }
    else if (ch == '`' && (!qc || qc == '"'))
    {
      FILE	*fp;
      pid_t	pid;
      char	*cmd, *ptr;
      size_t	expnlen;
      BUFFER	expn;
      int	line = 0;

      pc = tok->dptr;
      do {
	if ((pc = strpbrk (pc, "\\`")))
	{
	  /* skip any quoted chars */
	  if (*pc == '\\')
	    pc += 2;
	}
      } while (pc && *pc != '`');
      if (!pc)
      {
	dprint (1, (debugfile, "mutt_get_token: mismatched backticks\n"));
	return (-1);
      }
      cmd = mutt_substrdup (tok->dptr, pc);
      if ((pid = mutt_create_filter (cmd, NULL, &fp, NULL)) < 0)
      {
	dprint (1, (debugfile, "mutt_get_token: unable to fork command: %s", cmd));
	FREE (&cmd);
	return (-1);
      }
      FREE (&cmd);

      tok->dptr = pc + 1;

      /* read line */
      mutt_buffer_init (&expn);
      expn.data = mutt_read_line (NULL, &expn.dsize, fp, &line, 0);
      safe_fclose (&fp);
      mutt_wait_filter (pid);

      /* if we got output, make a new string consisting of the shell output
	 plus whatever else was left on the original line */
      /* BUT: If this is inside a quoted string, directly add output to 
       * the token */
      if (expn.data && qc)
      {
	mutt_buffer_addstr (dest, expn.data);
	FREE (&expn.data);
      }
      else if (expn.data)
      {
	expnlen = mutt_strlen (expn.data);
	tok->dsize = expnlen + mutt_strlen (tok->dptr) + 1;
	ptr = safe_malloc (tok->dsize);
	memcpy (ptr, expn.data, expnlen);
	strcpy (ptr + expnlen, tok->dptr);	/* __STRCPY_CHECKED__ */
	if (tok->destroy)
	  FREE (&tok->data);
	tok->data = ptr;
	tok->dptr = ptr;
	tok->destroy = 1; /* mark that the caller should destroy this data */
	ptr = NULL;
	FREE (&expn.data);
      }
    }
    else if (ch == '$' && (!qc || qc == '"') && (*tok->dptr == '{' || isalpha ((unsigned char) *tok->dptr)))
    {
      const char *env = NULL;
      char *var = NULL;
      int idx;

      if (*tok->dptr == '{')
      {
	tok->dptr++;
	if ((pc = strchr (tok->dptr, '}')))
	{
	  var = mutt_substrdup (tok->dptr, pc);
	  tok->dptr = pc + 1;
	}
      }
      else
      {
	for (pc = tok->dptr; isalnum ((unsigned char) *pc) || *pc == '_'; pc++)
	  ;
	var = mutt_substrdup (tok->dptr, pc);
	tok->dptr = pc;
      }
      if (var)
      {
        if ((env = getenv (var)) || (env = myvar_get (var)))
          mutt_buffer_addstr (dest, env);
        else if ((idx = mutt_option_index (var)) != -1)
        {
          /* expand settable mutt variables */
          char val[LONG_STRING];

          if (var_to_string (idx, val, sizeof (val)))
            mutt_buffer_addstr (dest, val);
        }
        FREE (&var);
      }
    }
    else
      mutt_buffer_addch (dest, ch);
  }
  mutt_buffer_addch (dest, 0); /* terminate the string */
  SKIPWS (tok->dptr);
  return 0;
}