pattern_t *mutt_pattern_comp (/* const */ char *s, int flags, BUFFER *err)
{
  pattern_t *curlist = NULL;
  pattern_t *tmp, *tmp2;
  pattern_t *last = NULL;
  int not = 0;
  int alladdr = 0;
  int or = 0;
  int implicit = 1;	/* used to detect logical AND operator */
  int isalias = 0;
  short thread_op;
  const struct pattern_flags *entry;
  char *p;
  char *buf;
  BUFFER ps;

  mutt_buffer_init (&ps);
  ps.dptr = s;
  ps.dsize = mutt_strlen (s);

  while (*ps.dptr)
  {
    SKIPWS (ps.dptr);
    switch (*ps.dptr)
    {
      case '^':
	ps.dptr++;
	alladdr = !alladdr;
	break;
      case '!':
	ps.dptr++;
	not = !not;
	break;
      case '@':
	ps.dptr++;
	isalias = !isalias;
	break;
      case '|':
	if (!or)
	{
	  if (!curlist)
	  {
	    snprintf (err->data, err->dsize, _("error in pattern at: %s"), ps.dptr);
	    return NULL;
	  }
	  if (curlist->next)
	  {
	    /* A & B | C == (A & B) | C */
	    tmp = new_pattern ();
	    tmp->op = MUTT_AND;
	    tmp->child = curlist;

	    curlist = tmp;
	    last = curlist;
	  }

	  or = 1;
	}
	ps.dptr++;
	implicit = 0;
	not = 0;
	alladdr = 0;
	isalias = 0;
	break;
      case '%':
      case '=':
      case '~':
	if (!*(ps.dptr + 1))
	{
	  snprintf (err->data, err->dsize, _("missing pattern: %s"), ps.dptr);
	  mutt_pattern_free (&curlist);
	  return NULL;
	}
        thread_op = 0;
	if (*(ps.dptr + 1) == '(')
          thread_op = MUTT_THREAD;
        else if ((*(ps.dptr + 1) == '<') && (*(ps.dptr + 2) == '('))
          thread_op = MUTT_PARENT;
        else if ((*(ps.dptr + 1) == '>') && (*(ps.dptr + 2) == '('))
          thread_op = MUTT_CHILDREN;
        if (thread_op)
        {
	  ps.dptr++; /* skip ~ */
          if (thread_op == MUTT_PARENT || thread_op == MUTT_CHILDREN)
            ps.dptr++;
	  p = find_matching_paren (ps.dptr + 1);
	  if (*p != ')')
	  {
	    snprintf (err->data, err->dsize, _("mismatched brackets: %s"), ps.dptr);
	    mutt_pattern_free (&curlist);
	    return NULL;
	  }
	  tmp = new_pattern ();
	  tmp->op = thread_op;
	  if (last)
	    last->next = tmp;
	  else
	    curlist = tmp;
	  last = tmp;
	  tmp->not ^= not;
	  tmp->alladdr |= alladdr;
	  tmp->isalias |= isalias;
	  not = 0;
	  alladdr = 0;
	  isalias = 0;
	  /* compile the sub-expression */
	  buf = mutt_substrdup (ps.dptr + 1, p);
	  if ((tmp2 = mutt_pattern_comp (buf, flags, err)) == NULL)
	  {
	    FREE (&buf);
	    mutt_pattern_free (&curlist);
	    return NULL;
	  }
	  FREE (&buf);
	  tmp->child = tmp2;
	  ps.dptr = p + 1; /* restore location */
	  break;
	}
        if (implicit && or)
	{
	  /* A | B & C == (A | B) & C */
	  tmp = new_pattern ();
	  tmp->op = MUTT_OR;
	  tmp->child = curlist;
	  curlist = tmp;
	  last = tmp;
	  or = 0;
	}

	tmp = new_pattern ();
	tmp->not = not;
	tmp->alladdr = alladdr;
	tmp->isalias = isalias;
        tmp->stringmatch = (*ps.dptr == '=') ? 1 : 0;
        tmp->groupmatch  = (*ps.dptr == '%') ? 1 : 0;
	not = 0;
	alladdr = 0;
	isalias = 0;

	if (last)
	  last->next = tmp;
	else
	  curlist = tmp;
	last = tmp;

	ps.dptr++; /* move past the ~ */
	if ((entry = lookup_tag (*ps.dptr)) == NULL)
	{
	  snprintf (err->data, err->dsize, _("%c: invalid pattern modifier"), *ps.dptr);
	  mutt_pattern_free (&curlist);
	  return NULL;
	}
	if (entry->class && (flags & entry->class) == 0)
	{
	  snprintf (err->data, err->dsize, _("%c: not supported in this mode"), *ps.dptr);
	  mutt_pattern_free (&curlist);
	  return NULL;
	}
	tmp->op = entry->op;

	ps.dptr++; /* eat the operator and any optional whitespace */
	SKIPWS (ps.dptr);

	if (entry->eat_arg)
	{
	  if (!*ps.dptr)
	  {
	    snprintf (err->data, err->dsize, "%s", _("missing parameter"));
	    mutt_pattern_free (&curlist);
	    return NULL;
	  }
	  if (entry->eat_arg (tmp, &ps, err) == -1)
	  {
	    mutt_pattern_free (&curlist);
	    return NULL;
	  }
	}
	implicit = 1;
	break;
      case '(':
	p = find_matching_paren (ps.dptr + 1);
	if (*p != ')')
	{
	  snprintf (err->data, err->dsize, _("mismatched parenthesis: %s"), ps.dptr);
	  mutt_pattern_free (&curlist);
	  return NULL;
	}
	/* compile the sub-expression */
	buf = mutt_substrdup (ps.dptr + 1, p);
	if ((tmp = mutt_pattern_comp (buf, flags, err)) == NULL)
	{
	  FREE (&buf);
	  mutt_pattern_free (&curlist);
	  return NULL;
	}
	FREE (&buf);
	if (last)
	  last->next = tmp;
	else
	  curlist = tmp;
	last = tmp;
	tmp->not ^= not;
	tmp->alladdr |= alladdr;
	tmp->isalias |= isalias;
	not = 0;
	alladdr = 0;
	isalias = 0;
	ps.dptr = p + 1; /* restore location */
	break;
      default:
	snprintf (err->data, err->dsize, _("error in pattern at: %s"), ps.dptr);
	mutt_pattern_free (&curlist);
	return NULL;
    }
  }
  if (!curlist)
  {
    strfcpy (err->data, _("empty pattern"), err->dsize);
    return NULL;
  }
  if (curlist->next)
  {
    tmp = new_pattern ();
    tmp->op = or ? MUTT_OR : MUTT_AND;
    tmp->child = curlist;
    curlist = tmp;
  }
  return (curlist);
}