static ADDRESS *mutt_expand_aliases_r (ADDRESS *a, LIST **expn)
{
  ADDRESS *head = NULL, *last = NULL, *t, *w;
  LIST *u;
  char i;
  const char *fqdn;
  
  while (a)
  {
    if (!a->group && !a->personal && a->mailbox && strchr (a->mailbox, '@') == NULL)
    {
      t = mutt_lookup_alias (a->mailbox);

      if (t)
      {	
        i = 0;
        for (u = *expn; u; u = u->next)
	{
	  if (mutt_strcmp (a->mailbox, u->data) == 0) /* alias already found */
	  {
	    dprint (1, (debugfile, "mutt_expand_aliases_r(): loop in alias found for '%s'\n", a->mailbox));
	    i = 1;
	    break;
	  }
	}

        if (!i)
	{
          u = safe_malloc (sizeof (LIST));
          u->data = safe_strdup (a->mailbox);
          u->next = *expn;
          *expn = u;
	  w = rfc822_cpy_adr (t, 0);
	  w = mutt_expand_aliases_r (w, expn);
	  if (head)
	    last->next = w;
	  else
	    head = last = w;
	  while (last && last->next)
	    last = last->next;
        }
	t = a;
	a = a->next;
	t->next = NULL;
	rfc822_free_address (&t);
	continue;
      }
      else
      {
	struct passwd *pw = getpwnam (a->mailbox);

	if (pw)
	{
	  char namebuf[STRING];
	  
	  mutt_gecos_name (namebuf, sizeof (namebuf), pw);
	  mutt_str_replace (&a->personal, namebuf);
	  
#ifdef EXACT_ADDRESS
	  FREE (&a->val);
#endif
	}
      }
    }

    if (head)
    {
      last->next = a;
      last = last->next;
    }
    else
      head = last = a;
    a = a->next;
    last->next = NULL;
  }

  if (option (OPTUSEDOMAIN) && (fqdn = mutt_fqdn(1)))
  {
    /* now qualify all local addresses */
    rfc822_qualify (head, fqdn);
  }

  return (head);
}