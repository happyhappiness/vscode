pattern_t *mutt_pattern_comp (/* const */ char *s, int flags, BUFFER *err)
{
  pattern_t *curlist = NULL;
  pattern_t *tmp, *tmp2;
  pattern_t *last = NULL;
  int not = 0;
  int alladdr = 0;
  int or = 0;
  int implicit = 1;	/* used to detect logical AND operator */
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
	    tmp->op = M_AND;
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
	if (*(ps.dptr + 1) == '(')
        {
	  ps.dptr ++; /* skip ~ */
	  p = find_matching_paren (ps.dptr + 1);
	  if (*p != ')')
	  {
	    snprintf (err->data, err->dsize, _("mismatched brackets: %s"), ps.dptr);
	    mutt_pattern_free (&curlist);
	    return NULL;
	  }
	  tmp = new_pattern ();
	  tmp->op = M_THREAD;
	  if (last)
	    last->next = tmp;
	  else
	    curlist = tmp;
	  last = tmp;
	  tmp->not ^= not;
	  tmp->alladdr |= alladdr;
	  not = 0;
	  alladdr = 0;
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
	  tmp->op = M_OR;
	  tmp->child = curlist;
	  curlist = tmp;
	  last = tmp;
	  or = 0;
	}

	tmp = new_pattern ();
	tmp->not = not;
	tmp->alladdr = alladdr;
        tmp->stringmatch = (*ps.dptr == '=') ? 1 : 0;
        tmp->groupmatch  = (*ps.dptr == '%') ? 1 : 0;
	not = 0;
	alladdr = 0;

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
	    snprintf (err->data, err->dsize, _("missing parameter"));
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
	not = 0;
	alladdr = 0;
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
    tmp->op = or ? M_OR : M_AND;
    tmp->child = curlist;
    curlist = tmp;
  }
  return (curlist);
}