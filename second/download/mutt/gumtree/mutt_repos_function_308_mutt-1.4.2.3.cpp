static LIST *mutt_parse_references (char *s, int in_reply_to)
{
  LIST *t, *lst = NULL;
  int m, n = 0;
  char *o = NULL, *new, *at;

  while ((s = strtok (s, " \t;")) != NULL)
  {
    /*
     * some mail clients add other garbage besides message-ids, so do a quick
     * check to make sure this looks like a valid message-id
     * some idiotic clients also break their message-ids between lines, deal
     * with that too (give up if it's more than two lines, though)
     */
    t = NULL;
    new = NULL;

    if (*s == '<')
    {
      n = strlen (s);
      if (s[n-1] != '>')
      {
	o = s;
	s = NULL;
	continue;
      }

      new = safe_strdup (s);
    }
    else if (o)
    {
      m = strlen (s);
      if (s[m - 1] == '>')
      {
	new = safe_malloc (sizeof (char) * (n + m + 1));
	strcpy (new, o);	/* __STRCPY_CHECKED__ */
	strcpy (new + n, s);	/* __STRCPY_CHECKED__ */
      }
    }
    if (new)
    {
      /* make sure that this really does look like a message-id.
       * it should have exactly one @, and if we're looking at
       * an in-reply-to header, make sure that the part before
       * the @ has more than eight characters or it's probably
       * an email address
       */
      if (!(at = strchr (new, '@')) || strchr (at + 1, '@')
	  || (in_reply_to && at - new <= 8))
	safe_free ((void **) &new);
      else
      {
	t = (LIST *) safe_malloc (sizeof (LIST));
	t->data = new;
	t->next = lst;
	lst = t;
      }
    }
    o = NULL;
    s = NULL;
  }

  return (lst);
}