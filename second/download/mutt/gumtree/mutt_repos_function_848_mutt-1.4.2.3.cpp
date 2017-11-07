ADDRESS *rfc822_parse_adrlist (ADDRESS *top, const char *s)
{
  const char *begin, *ps;
  char comment[STRING], phrase[STRING];
  size_t phraselen = 0, commentlen = 0;
  ADDRESS *cur, *last = NULL;
  
  RFC822Error = 0;

  last = top;
  while (last && last->next)
    last = last->next;

  SKIPWS (s);
  begin = s;
  while (*s)
  {
    if (*s == ',')
    {
      if (phraselen)
      {
	terminate_buffer (phrase, phraselen);
	add_addrspec (&top, &last, phrase, comment, &commentlen, sizeof (comment) - 1);
      }
      else if (commentlen && last && !last->personal)
      {
	terminate_buffer (comment, commentlen);
	last->personal = safe_strdup (comment);
      }

#ifdef EXACT_ADDRESS
      if (last && !last->val)
	last->val = mutt_substrdup (begin, s);
#endif
      commentlen = 0;
      phraselen = 0;
      s++;
      begin = s;
      SKIPWS (begin);
    }
    else if (*s == '(')
    {
      if (commentlen && commentlen < sizeof (comment) - 1)
	comment[commentlen++] = ' ';
      if ((ps = next_token (s, comment, &commentlen, sizeof (comment) - 1)) == NULL)
      {
	rfc822_free_address (&top);
	return NULL;
      }
      s = ps;
    }
    else if (*s == ':')
    {
      cur = rfc822_new_address ();
      terminate_buffer (phrase, phraselen);
      cur->mailbox = safe_strdup (phrase);
      cur->group = 1;

      if (last)
	last->next = cur;
      else
	top = cur;
      last = cur;

#ifdef EXACT_ADDRESS
      last->val = mutt_substrdup (begin, s);
#endif

      phraselen = 0;
      commentlen = 0;
      s++;
      begin = s;
      SKIPWS (begin);
    }
    else if (*s == ';')
    {
      if (phraselen)
      {
	terminate_buffer (phrase, phraselen);
	add_addrspec (&top, &last, phrase, comment, &commentlen, sizeof (comment) - 1);
      }
      else if (commentlen && last && !last->personal)
      {
	terminate_buffer (comment, commentlen);
	last->personal = safe_strdup (comment);
      }
#ifdef EXACT_ADDRESS
      if (last && !last->val)
	last->val = mutt_substrdup (begin, s);
#endif

      /* add group terminator */
      cur = rfc822_new_address ();
      if (last)
      {
	last->next = cur;
	last = cur;
      }

      phraselen = 0;
      commentlen = 0;
      s++;
      begin = s;
      SKIPWS (begin);
    }
    else if (*s == '<')
    {
      terminate_buffer (phrase, phraselen);
      cur = rfc822_new_address ();
      if (phraselen)
      {
	if (cur->personal)
	  FREE (&cur->personal);
	/* if we get something like "Michael R. Elkins" remove the quotes */
	rfc822_dequote_comment (phrase);
	cur->personal = safe_strdup (phrase);
      }
      if ((ps = parse_route_addr (s + 1, comment, &commentlen, sizeof (comment) - 1, cur)) == NULL)
      {
	rfc822_free_address (&top);
	rfc822_free_address (&cur);
	return NULL;
      }

      if (last)
	last->next = cur;
      else
	top = cur;
      last = cur;

      phraselen = 0;
      commentlen = 0;
      s = ps;
    }
    else
    {
      if (phraselen && phraselen < sizeof (phrase) - 1 && *s != '.')
	phrase[phraselen++] = ' ';
      if ((ps = next_token (s, phrase, &phraselen, sizeof (phrase) - 1)) == NULL)
      {
	rfc822_free_address (&top);
	return NULL;
      }
      s = ps;
    }
    SKIPWS (s);
  }
  
  if (phraselen)
  {
    terminate_buffer (phrase, phraselen);
    terminate_buffer (comment, commentlen);
    add_addrspec (&top, &last, phrase, comment, &commentlen, sizeof (comment) - 1);
  }
  else if (commentlen && last && !last->personal)
  {
    terminate_buffer (comment, commentlen);
    last->personal = safe_strdup (comment);
  }
#ifdef EXACT_ADDRESS
  if (last)
    last->val = mutt_substrdup (begin, s);
#endif

  return top;
}