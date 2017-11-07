static int parse_set (BUFFER *tmp, BUFFER *s, unsigned long data, BUFFER *err)
{
  int idx, query, unset, inv, reset, r = 0;
  char *p, scratch[_POSIX_PATH_MAX];

  while (MoreArgs (s))
  {
    /* reset state variables */
    query = 0;
    unset = data & M_SET_UNSET;
    inv = data & M_SET_INV;
    reset = data & M_SET_RESET;

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
    mutt_extract_token (tmp, s, M_TOKEN_EQUAL);

    if ((idx = mutt_option_index (tmp->data)) == -1 &&
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
	for (idx = 0; MuttVars[idx].option; idx++)
	  mutt_restore_default (&MuttVars[idx]);
	return 0;
      }
      else
	mutt_restore_default (&MuttVars[idx]);
    } 
    else if (DTYPE (MuttVars[idx].type) == DT_BOOL)
    { 
      if (s && *s->dptr == '=')
      {
	if (unset || inv || query)
	{
	  snprintf (err->data, err->dsize, "Usage: set variable=yes|no");
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
	  snprintf (err->data, err->dsize, "Usage: set variable=yes|no");
	  return (-1);
	}
      }

      if (query)
      {
	snprintf (err->data, err->dsize, option (MuttVars[idx].data)
			? _("%s is set") : _("%s is unset"), tmp->data);
	return 0;
      }

      if (unset)
	unset_option (MuttVars[idx].data);
      else if (inv)
	toggle_option (MuttVars[idx].data);
      else
	set_option (MuttVars[idx].data);
    }
    else if (DTYPE (MuttVars[idx].type) == DT_STR ||
	     DTYPE (MuttVars[idx].type) == DT_PATH ||
	     DTYPE (MuttVars[idx].type) == DT_ADDR)
    {
      if (unset)
      {
	if (DTYPE (MuttVars[idx].type) == DT_ADDR)
	  rfc822_free_address ((ADDRESS **) MuttVars[idx].data);
	else
	  safe_free ((void **) MuttVars[idx].data);
      }
      else if (query || *s->dptr != '=')
      {
	char _tmp[STRING];
	char *val = NULL;
	
	if (DTYPE (MuttVars[idx].type) == DT_ADDR)
	{
	  _tmp[0] = '\0';
	  rfc822_write_address (_tmp, sizeof (_tmp), *((ADDRESS **) MuttVars[idx].data));
	  val = _tmp;
	}
	else
	  val = *((char **) MuttVars[idx].data);
	
	/* user requested the value of this variable */
	snprintf (err->data, err->dsize, "%s=\"%s\"", MuttVars[idx].option,
		  NONULL (val));
	break;
      }
      else
      {
        s->dptr++;

        /* copy the value of the string */
        if (DTYPE (MuttVars[idx].type) == DT_ADDR)
	  rfc822_free_address ((ADDRESS **) MuttVars[idx].data);
        else
	  FREE (MuttVars[idx].data);

        mutt_extract_token (tmp, s, 0);
        if (DTYPE (MuttVars[idx].type) == DT_PATH)
        {
	  strfcpy (scratch, tmp->data, sizeof (scratch));
	  mutt_expand_path (scratch, sizeof (scratch));
	  *((char **) MuttVars[idx].data) = safe_strdup (scratch);
        }
        else if (DTYPE (MuttVars[idx].type) == DT_STR)
        {
	  *((char **) MuttVars[idx].data) = safe_strdup (tmp->data);
	  if (mutt_strcmp (MuttVars[idx].option, "charset") == 0)
	    mutt_set_charset (Charset);
        }
        else
        {
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
	snprintf (err->data, err->dsize, "%s=\"%s\"", MuttVars[idx].option,
		  NONULL (ptr->pattern));
	break;
      }

      if (option(OPTATTACHMSG) && (!mutt_strcmp(MuttVars[idx].option, "alternates")
				   || !mutt_strcmp(MuttVars[idx].option, "reply_regexp")))
      {
	snprintf (err->data, err->dsize, "Operation not permitted when in attach-message mode.");
	r = -1;
	break;
      }
      
      s->dptr++;

      /* copy the value of the string */
      mutt_extract_token (tmp, s, 0);

      if (!ptr->pattern || mutt_strcmp (ptr->pattern, tmp->data) != 0)
      {
	int not = 0;

	/* $alternates is case-insensitive,
	   $mask is case-sensitive */
	if (mutt_strcmp (MuttVars[idx].option, "alternates") == 0)
	  flags |= REG_ICASE;
	else if (mutt_strcmp (MuttVars[idx].option, "mask") != 0)
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
	  regfree (rx);
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
	
	if(Context && Context->msgcount &&
	   mutt_strcmp(MuttVars[idx].option, "alternates") == 0)
	{
	  int i;
	  
	  for(i = 0; i < Context->msgcount; i++)
	    Context->hdrs[i]->recip_valid = 0;
	}
      }
    }
    else if (DTYPE(MuttVars[idx].type) == DT_MAGIC)
    {
      if (query || *s->dptr != '=')
      {
	switch (DefaultMagic)
	{
	  case M_MBOX:
	    p = "mbox";
	    break;
	  case M_MMDF:
	    p = "MMDF";
	    break;
	  case M_KENDRA:
	    p = "KENDRA";
	    break;
	  case M_MH:
	    p = "MH";
	    break;
	  case M_MAILDIR:
	    p = "Maildir";
	    break;
	  default:
	    p = "unknown";
	    break;
	}
	snprintf (err->data, err->dsize, "%s=%s", MuttVars[idx].option, p);
	break;
      }

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
      int val;
      char *t;

      if (query || *s->dptr != '=')
      {
	/* user requested the value of this variable */
	snprintf (err->data, err->dsize, "%s=%d", MuttVars[idx].option, *ptr);
	break;
      }

      s->dptr++;

      mutt_extract_token (tmp, s, 0);
      val = strtol (tmp->data, &t, 0);

      if (!*tmp->data || *t || (short) val != val)
      {
	snprintf (err->data, err->dsize, _("%s: invalid value"), tmp->data);
	r = -1;
	break;
      }
      else
	*ptr = (short) val;

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
    }
    else if (DTYPE (MuttVars[idx].type) == DT_QUAD)
    {
      if (query)
      {
	char *vals[] = { "no", "yes", "ask-no", "ask-yes" };

	snprintf (err->data, err->dsize, "%s=%s", MuttVars[idx].option,
		  vals [ quadoption (MuttVars[idx].data) ]);
	break;
      }

      if (*s->dptr == '=')
      {
	s->dptr++;
	mutt_extract_token (tmp, s, 0);
	if (ascii_strcasecmp ("yes", tmp->data) == 0)
	  set_quadoption (MuttVars[idx].data, M_YES);
	else if (ascii_strcasecmp ("no", tmp->data) == 0)
	  set_quadoption (MuttVars[idx].data, M_NO);
	else if (ascii_strcasecmp ("ask-yes", tmp->data) == 0)
	  set_quadoption (MuttVars[idx].data, M_ASKYES);
	else if (ascii_strcasecmp ("ask-no", tmp->data) == 0)
	  set_quadoption (MuttVars[idx].data, M_ASKNO);
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
	  set_quadoption (MuttVars[idx].data, M_NO);
	else
	  set_quadoption (MuttVars[idx].data, M_YES);
      }
    }
    else if (DTYPE (MuttVars[idx].type) == DT_SORT)
    {
      const struct mapping_t *map;

      switch (MuttVars[idx].type & DT_SUBTYPE_MASK)
      {
	case DT_SORT_ALIAS:
	  map = SortAliasMethods;
	  break;
	case DT_SORT_BROWSER:
	  map = SortBrowserMethods;
	  break;
#ifdef HAVE_PGP
	case DT_SORT_KEYS:
	  map = SortKeyMethods;
	  break;
#endif
	case DT_SORT_AUX:
	  map = SortAuxMethods;
	  break;
	default:
	  map = SortMethods;
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
  }
  return (r);
}