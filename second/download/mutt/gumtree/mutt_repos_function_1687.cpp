static int parse_set (BUFFER *tmp, BUFFER *s, unsigned long data, BUFFER *err)
{
  int query, unset, inv, reset, r = 0;
  int idx = -1;
  const char *p;
  char scratch[_POSIX_PATH_MAX];
  char* myvar;

  while (MoreArgs (s))
  {
    /* reset state variables */
    query = 0;
    unset = data & MUTT_SET_UNSET;
    inv = data & MUTT_SET_INV;
    reset = data & MUTT_SET_RESET;
    myvar = NULL;

    if (*s->dptr == '?')
    {
      query = 1;
      s->dptr++;
    }
    else if (mutt_strncmp ("no", s->dptr, 2) == 0)
    {
      s->dptr += 2;
      unset = !unset;
    }
    else if (mutt_strncmp ("inv", s->dptr, 3) == 0)
    {
      s->dptr += 3;
      inv = !inv;
    }
    else if (*s->dptr == '&')
    {
      reset = 1;
      s->dptr++;
    }

    /* get the variable name */
    mutt_extract_token (tmp, s, MUTT_TOKEN_EQUAL);

    if (!mutt_strncmp ("my_", tmp->data, 3))
      myvar = tmp->data;
    else if ((idx = mutt_option_index (tmp->data)) == -1 &&
	!(reset && !mutt_strcmp ("all", tmp->data)))
    {
      snprintf (err->data, err->dsize, _("%s: unknown variable"), tmp->data);
      return (-1);
    }
    SKIPWS (s->dptr);

    if (reset)
    {
      if (query || unset || inv)
      {
	snprintf (err->data, err->dsize, _("prefix is illegal with reset"));
	return (-1);
      }

      if (s && *s->dptr == '=')
      {
	snprintf (err->data, err->dsize, _("value is illegal with reset"));
	return (-1);
      }
     
      if (!mutt_strcmp ("all", tmp->data))
      {
	if (CurrentMenu == MENU_PAGER)
	{
	  snprintf (err->data, err->dsize, _("Not available in this menu."));
	  return (-1);
	}
	for (idx = 0; MuttVars[idx].option; idx++)
	  mutt_restore_default (&MuttVars[idx]);
	set_option (OPTFORCEREDRAWINDEX);
	set_option (OPTFORCEREDRAWPAGER);
	set_option (OPTSORTSUBTHREADS);
	set_option (OPTNEEDRESORT);
	set_option (OPTRESORTINIT);
	set_option (OPTREDRAWTREE);
	return 0;
      }
      else
      {
	CHECK_PAGER;
        if (myvar)
          myvar_del (myvar);
        else
          mutt_restore_default (&MuttVars[idx]);
      }
    } 
    else if (!myvar && DTYPE (MuttVars[idx].type) == DT_BOOL)
    { 
      if (s && *s->dptr == '=')
      {
	if (unset || inv || query)
	{
	  snprintf (err->data, err->dsize, _("Usage: set variable=yes|no"));
	  return (-1);
	}

	s->dptr++;
	mutt_extract_token (tmp, s, 0);
	if (ascii_strcasecmp ("yes", tmp->data) == 0)
	  unset = inv = 0;
	else if (ascii_strcasecmp ("no", tmp->data) == 0)
	  unset = 1;
	else
	{
	  snprintf (err->data, err->dsize, _("Usage: set variable=yes|no"));
	  return (-1);
	}
      }

      if (query)
      {
	snprintf (err->data, err->dsize, option (MuttVars[idx].data)
			? _("%s is set") : _("%s is unset"), tmp->data);
	return 0;
      }

      CHECK_PAGER;
      if (unset)
	unset_option (MuttVars[idx].data);
      else if (inv)
	toggle_option (MuttVars[idx].data);
      else
	set_option (MuttVars[idx].data);
    }
    else if (myvar || DTYPE (MuttVars[idx].type) == DT_STR ||
	     DTYPE (MuttVars[idx].type) == DT_PATH ||
	     DTYPE (MuttVars[idx].type) == DT_ADDR)
    {
      if (unset)
      {
	CHECK_PAGER;
        if (myvar)
          myvar_del (myvar);
	else if (DTYPE (MuttVars[idx].type) == DT_ADDR)
	  rfc822_free_address ((ADDRESS **) MuttVars[idx].data);
	else
	  /* MuttVars[idx].data is already 'char**' (or some 'void**') or... 
	   * so cast to 'void*' is okay */
	  FREE ((void *) MuttVars[idx].data);		/* __FREE_CHECKED__ */
      }
      else if (query || *s->dptr != '=')
      {
	char _tmp[LONG_STRING];
	const char *val = NULL;

        if (myvar)
        {
          if ((val = myvar_get (myvar)))
          {
	    pretty_var (err->data, err->dsize, myvar, val);
            break;
          }
          else
          {
            snprintf (err->data, err->dsize, _("%s: unknown variable"), myvar);
            return (-1);
          }
        }
	else if (DTYPE (MuttVars[idx].type) == DT_ADDR)
	{
	  _tmp[0] = '\0';
	  rfc822_write_address (_tmp, sizeof (_tmp), *((ADDRESS **) MuttVars[idx].data), 0);
	  val = _tmp;
	}
	else if (DTYPE (MuttVars[idx].type) == DT_PATH)
	{
	  _tmp[0] = '\0';
	  strfcpy (_tmp, NONULL(*((char **) MuttVars[idx].data)), sizeof (_tmp));
	  mutt_pretty_mailbox (_tmp, sizeof (_tmp));
	  val = _tmp;
	}
	else
	  val = *((char **) MuttVars[idx].data);
	
	/* user requested the value of this variable */
	pretty_var (err->data, err->dsize, MuttVars[idx].option, NONULL(val));
	break;
      }
      else
      {
	CHECK_PAGER;
        s->dptr++;

        if (myvar)
	{
	  /* myvar is a pointer to tmp and will be lost on extract_token */
	  myvar = safe_strdup (myvar);
          myvar_del (myvar);
	}

        mutt_extract_token (tmp, s, 0);

        if (myvar)
        {
          myvar_set (myvar, tmp->data);
          FREE (&myvar);
	  myvar="don't resort";
        }
        else if (DTYPE (MuttVars[idx].type) == DT_PATH)
        {
	  /* MuttVars[idx].data is already 'char**' (or some 'void**') or... 
	   * so cast to 'void*' is okay */
	  FREE ((void *) MuttVars[idx].data);		/* __FREE_CHECKED__ */

	  strfcpy (scratch, tmp->data, sizeof (scratch));
	  mutt_expand_path (scratch, sizeof (scratch));
	  *((char **) MuttVars[idx].data) = safe_strdup (scratch);
        }
        else if (DTYPE (MuttVars[idx].type) == DT_STR)
        {
	  if ((strstr (MuttVars[idx].option, "charset") &&
	       check_charset (&MuttVars[idx], tmp->data) < 0) |
	      /* $charset can't be empty, others can */
	      (strcmp(MuttVars[idx].option, "charset") == 0 && ! *tmp->data))
	  {
	    snprintf (err->data, err->dsize, _("Invalid value for option %s: \"%s\""),
		      MuttVars[idx].option, tmp->data);
	    return (-1);
	  }

	  FREE ((void *) MuttVars[idx].data);		/* __FREE_CHECKED__ */
	  *((char **) MuttVars[idx].data) = safe_strdup (tmp->data);
	  if (mutt_strcmp (MuttVars[idx].option, "charset") == 0)
	    mutt_set_charset (Charset);
        }
        else
        {
	  rfc822_free_address ((ADDRESS **) MuttVars[idx].data);
	  *((ADDRESS **) MuttVars[idx].data) = rfc822_parse_adrlist (NULL, tmp->data);
        }
      }
    }
    else if (DTYPE(MuttVars[idx].type) == DT_RX)
    {
      REGEXP *ptr = (REGEXP *) MuttVars[idx].data;
      regex_t *rx;
      int e, flags = 0;

      if (query || *s->dptr != '=')
      {
	/* user requested the value of this variable */
	pretty_var (err->data, err->dsize, MuttVars[idx].option, NONULL(ptr->pattern));
	break;
      }

      if (option(OPTATTACHMSG) && !mutt_strcmp(MuttVars[idx].option, "reply_regexp"))
      {
	snprintf (err->data, err->dsize, "Operation not permitted when in attach-message mode.");
	r = -1;
	break;
      }
      
      CHECK_PAGER;
      s->dptr++;

      /* copy the value of the string */
      mutt_extract_token (tmp, s, 0);

      if (!ptr->pattern || mutt_strcmp (ptr->pattern, tmp->data) != 0)
      {
	int not = 0;

	/* $mask is case-sensitive */
	if (mutt_strcmp (MuttVars[idx].option, "mask") != 0)
	  flags |= mutt_which_case (tmp->data);

	p = tmp->data;
	if (mutt_strcmp (MuttVars[idx].option, "mask") == 0)
	{
	  if (*p == '!')
	  {
	    not = 1;
	    p++;
	  }
	}
	  
	rx = (regex_t *) safe_malloc (sizeof (regex_t));
	if ((e = REGCOMP (rx, p, flags)) != 0)
	{
	  regerror (e, rx, err->data, err->dsize);
	  FREE (&rx);
	  break;
	}

	/* get here only if everything went smootly */
	if (ptr->pattern)
	{
	  FREE (&ptr->pattern);
	  regfree ((regex_t *) ptr->rx);
	  FREE (&ptr->rx);
	}

	ptr->pattern = safe_strdup (tmp->data);
	ptr->rx = rx;
	ptr->not = not;

	/* $reply_regexp and $alterantes require special treatment */
	
	if (Context && Context->msgcount &&
	    mutt_strcmp (MuttVars[idx].option, "reply_regexp") == 0)
	{
	  regmatch_t pmatch[1];
	  int i;
	  
#define CUR_ENV Context->hdrs[i]->env
	  for (i = 0; i < Context->msgcount; i++)
	  {
	    if (CUR_ENV && CUR_ENV->subject)
	    {
	      CUR_ENV->real_subj = (regexec (ReplyRegexp.rx,
				    CUR_ENV->subject, 1, pmatch, 0)) ?
				    CUR_ENV->subject : 
				    CUR_ENV->subject + pmatch[0].rm_eo;
	    }
	  }
#undef CUR_ENV
	}
      }
    }
    else if (DTYPE(MuttVars[idx].type) == DT_MAGIC)
    {
      if (query || *s->dptr != '=')
      {
	switch (DefaultMagic)
	{
	  case MUTT_MBOX:
	    p = "mbox";
	    break;
	  case MUTT_MMDF:
	    p = "MMDF";
	    break;
	  case MUTT_MH:
	    p = "MH";
	    break;
	  case MUTT_MAILDIR:
	    p = "Maildir";
	    break;
	  default:
	    p = "unknown";
	    break;
	}
	snprintf (err->data, err->dsize, "%s=%s", MuttVars[idx].option, p);
	break;
      }

      CHECK_PAGER;
      s->dptr++;

      /* copy the value of the string */
      mutt_extract_token (tmp, s, 0);
      if (mx_set_magic (tmp->data))
      {
	snprintf (err->data, err->dsize, _("%s: invalid mailbox type"), tmp->data);
	r = -1;
	break;
      }
    }
    else if (DTYPE(MuttVars[idx].type) == DT_NUM)
    {
      short *ptr = (short *) MuttVars[idx].data;
      short val;
      int rc;

      if (query || *s->dptr != '=')
      {
	val = *ptr;
	/* compatibility alias */
	if (mutt_strcmp (MuttVars[idx].option, "wrapmargin") == 0)
	  val = *ptr < 0 ? -*ptr : 0;

	/* user requested the value of this variable */
	snprintf (err->data, err->dsize, "%s=%d", MuttVars[idx].option, val);
	break;
      }

      CHECK_PAGER;
      s->dptr++;

      mutt_extract_token (tmp, s, 0);
      rc = mutt_atos (tmp->data, (short *) &val);

      if (rc < 0 || !*tmp->data)
      {
	snprintf (err->data, err->dsize, _("%s: invalid value (%s)"), tmp->data,
		  rc == -1 ? _("format error") : _("number overflow"));
	r = -1;
	break;
      }
      else
	*ptr = val;

      /* these ones need a sanity check */
      if (mutt_strcmp (MuttVars[idx].option, "history") == 0)
      {
	if (*ptr < 0)
	  *ptr = 0;
	mutt_init_history ();
      }
      else if (mutt_strcmp (MuttVars[idx].option, "pager_index_lines") == 0)
      {
	if (*ptr < 0)
	  *ptr = 0;
      }
      else if (mutt_strcmp (MuttVars[idx].option, "wrapmargin") == 0)
      {
	if (*ptr < 0)
	  *ptr = 0;
	else
	  *ptr = -*ptr;
      }
#ifdef USE_IMAP
      else if (mutt_strcmp (MuttVars[idx].option, "imap_pipeline_depth") == 0)
      {
        if (*ptr < 0)
          *ptr = 0;
      }
#endif
    }
    else if (DTYPE (MuttVars[idx].type) == DT_QUAD)
    {
      if (query)
      {
	static const char * const vals[] = { "no", "yes", "ask-no", "ask-yes" };

	snprintf (err->data, err->dsize, "%s=%s", MuttVars[idx].option,
		  vals [ quadoption (MuttVars[idx].data) ]);
	break;
      }

      CHECK_PAGER;
      if (*s->dptr == '=')
      {
	s->dptr++;
	mutt_extract_token (tmp, s, 0);
	if (ascii_strcasecmp ("yes", tmp->data) == 0)
	  set_quadoption (MuttVars[idx].data, MUTT_YES);
	else if (ascii_strcasecmp ("no", tmp->data) == 0)
	  set_quadoption (MuttVars[idx].data, MUTT_NO);
	else if (ascii_strcasecmp ("ask-yes", tmp->data) == 0)
	  set_quadoption (MuttVars[idx].data, MUTT_ASKYES);
	else if (ascii_strcasecmp ("ask-no", tmp->data) == 0)
	  set_quadoption (MuttVars[idx].data, MUTT_ASKNO);
	else
	{
	  snprintf (err->data, err->dsize, _("%s: invalid value"), tmp->data);
	  r = -1;
	  break;
	}
      }
      else
      {
	if (inv)
	  toggle_quadoption (MuttVars[idx].data);
	else if (unset)
	  set_quadoption (MuttVars[idx].data, MUTT_NO);
	else
	  set_quadoption (MuttVars[idx].data, MUTT_YES);
      }
    }
    else if (DTYPE (MuttVars[idx].type) == DT_SORT)
    {
      const struct mapping_t *map = NULL;

      switch (MuttVars[idx].type & DT_SUBTYPE_MASK)
      {
	case DT_SORT_ALIAS:
	  map = SortAliasMethods;
	  break;
	case DT_SORT_BROWSER:
	  map = SortBrowserMethods;
	  break;
	case DT_SORT_KEYS:
          if ((WithCrypto & APPLICATION_PGP))
            map = SortKeyMethods;
	  break;
	case DT_SORT_AUX:
	  map = SortAuxMethods;
	  break;
	case DT_SORT_SIDEBAR:
	  map = SortSidebarMethods;
	  break;
	default:
	  map = SortMethods;
	  break;
      }

      if (!map)
      {
	snprintf (err->data, err->dsize, _("%s: Unknown type."), MuttVars[idx].option);
	r = -1;
	break;
      }
      
      if (query || *s->dptr != '=')
      {
	p = mutt_getnamebyvalue (*((short *) MuttVars[idx].data) & SORT_MASK, map);

	snprintf (err->data, err->dsize, "%s=%s%s%s", MuttVars[idx].option,
		  (*((short *) MuttVars[idx].data) & SORT_REVERSE) ? "reverse-" : "",
		  (*((short *) MuttVars[idx].data) & SORT_LAST) ? "last-" : "",
		  p);
	return 0;
      }
      CHECK_PAGER;
      s->dptr++;
      mutt_extract_token (tmp, s , 0);

      if (parse_sort ((short *) MuttVars[idx].data, tmp->data, map, err) == -1)
      {
	r = -1;
	break;
      }
    }
    else
    {
      snprintf (err->data, err->dsize, _("%s: unknown type"), MuttVars[idx].option);
      r = -1;
      break;
    }

    if (!myvar)
    {
      if (MuttVars[idx].flags & R_INDEX)
        set_option (OPTFORCEREDRAWINDEX);
      if (MuttVars[idx].flags & R_PAGER)
        set_option (OPTFORCEREDRAWPAGER);
      if (MuttVars[idx].flags & R_RESORT_SUB)
        set_option (OPTSORTSUBTHREADS);
      if (MuttVars[idx].flags & R_RESORT)
        set_option (OPTNEEDRESORT);
      if (MuttVars[idx].flags & R_RESORT_INIT)
        set_option (OPTRESORTINIT);
      if (MuttVars[idx].flags & R_TREE)
        set_option (OPTREDRAWTREE);
      if (MuttVars[idx].flags & R_REFLOW)
        mutt_reflow_windows ();
#ifdef USE_SIDEBAR
      if (MuttVars[idx].flags & R_SIDEBAR)
        SidebarNeedsRedraw = 1;
#endif
    }
  }
  return (r);
}