int mutt_builtin_editor (const char *path, HEADER *msg, HEADER *cur)
{
  char **buf = NULL;
  int bufmax = 0, buflen = 0;
  char tmp[LONG_STRING];
  int abort = 0;
  int done = 0;
  int i;
  char *p;
  
  scrollok (stdscr, TRUE);

  be_edit_header (msg->env, 0);

  addstr (_("(End message with a . on a line by itself)\n"));

  buf = be_snarf_file (path, buf, &bufmax, &buflen, 0);

  tmp[0] = 0;
  while (!done)
  {
    if (mutt_enter_string (tmp, sizeof (tmp), LINES-1, 0, 0) == -1)
    {
      tmp[0] = 0;
      continue;
    }
    addch ('\n');

    if (EscChar && tmp[0] == EscChar[0] && tmp[1] != EscChar[0])
    {
      /* remove trailing whitespace from the line */
      p = tmp + mutt_strlen (tmp) - 1;
      while (p >= tmp && ISSPACE (*p))
	*p-- = 0;

      p = tmp + 2;
      SKIPWS (p);

      switch (tmp[1])
      {
	case '?':
	  addstr (_(EditorHelp1));
          addstr (_(EditorHelp2));
	  break;
	case 'b':
	  msg->env->bcc = mutt_parse_adrlist (msg->env->bcc, p);
	  msg->env->bcc = mutt_expand_aliases (msg->env->bcc);
	  break;
	case 'c':
	  msg->env->cc = mutt_parse_adrlist (msg->env->cc, p);
	  msg->env->cc = mutt_expand_aliases (msg->env->cc);
	  break;
	case 'h':
	  be_edit_header (msg->env, 1);
	  break;
	case 'F':
	case 'f':
	case 'm':
	case 'M':
	  if (Context)
	  {
	    if (!*p && cur)
 	    {
	      /* include the current message */
	      p = tmp + mutt_strlen (tmp) + 1;
	      snprintf (tmp + mutt_strlen (tmp), sizeof (tmp) - mutt_strlen (tmp), " %d",
								cur->msgno + 1);
	    }
	    buf = be_include_messages (p, buf, &bufmax, &buflen,
				       (ascii_tolower (tmp[1]) == 'm'),
				       (ascii_isupper ((unsigned char) tmp[1])));
	  }
	  else
	    addstr (_("No mailbox.\n"));
	  break;
	case 'p':
	  addstr ("-----\n");
	  addstr (_("Message contains:\n"));
	  be_print_header (msg->env);
	  for (i = 0; i < buflen; i++)
	    addstr (buf[i]);
	  addstr (_("(continue)\n"));
	  break;
	case 'q':
	  done = 1;
	  break;
	case 'r':
	  if (*p)
          {
	    strncpy(tmp, p, sizeof(tmp));
	    mutt_expand_path(tmp, sizeof(tmp));
	    buf = be_snarf_file (tmp, buf, &bufmax, &buflen, 1);
          }
	  else
	    addstr (_("missing filename.\n"));
	  break;
	case 's':
	  mutt_str_replace (&msg->env->subject, p);
	  break;
	case 't':
	  msg->env->to = rfc822_parse_adrlist (msg->env->to, p);
	  msg->env->to = mutt_expand_aliases (msg->env->to);
	  break;
	case 'u':
	  if (buflen)
	  {
	    buflen--;
	    strfcpy (tmp, buf[buflen], sizeof (tmp));
	    tmp[mutt_strlen (tmp)-1] = 0;
	    FREE (&buf[buflen]);
	    buf[buflen] = NULL;
	    continue;
	  }
	  else
	    addstr (_("No lines in message.\n"));
	  break;

	case 'e':
	case 'v':
	  if (be_barf_file (path, buf, buflen) == 0)
	  {
	    char *tag, *err;
	    be_free_memory (buf, buflen);
	    buf = NULL;
	    bufmax = buflen = 0;

	    if (option (OPTEDITHDRS))
	    {
	      mutt_env_to_local (msg->env);
	      mutt_edit_headers (NONULL(Visual), path, msg, NULL, 0);
	      if (mutt_env_to_idna (msg->env, &tag, &err))
		printw (_("Bad IDN in %s: '%s'\n"), tag, err);
	    }
	    else
	      mutt_edit_file (NONULL(Visual), path);

	    buf = be_snarf_file (path, buf, &bufmax, &buflen, 0);

	    addstr (_("(continue)\n"));
	  }
	  break;
	case 'w':
	  be_barf_file (*p ? p : path, buf, buflen);
	  break;
	case 'x':
	  abort = 1;
	  done = 1;
	  break;
	default:
	  printw (_("%s: unknown editor command (~? for help)\n"), tmp);
	  break;
      }
    }
    else if (mutt_strcmp (".", tmp) == 0)
      done = 1;
    else
    {
      safe_strcat (tmp, sizeof (tmp), "\n");
      if (buflen == bufmax)
	safe_realloc (&buf, sizeof (char *) * (bufmax += 25));
      buf[buflen++] = safe_strdup (tmp[1] == '~' ? tmp + 1 : tmp);
    }
    
    tmp[0] = 0;
  }

  if (!abort) be_barf_file (path, buf, buflen);
  be_free_memory (buf, buflen);

  return (abort ? -1 : 0);
}