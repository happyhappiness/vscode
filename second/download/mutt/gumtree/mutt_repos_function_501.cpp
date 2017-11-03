static PARAMETER *parse_parameters (const char *s)
{
  PARAMETER *head = 0, *cur = 0, *new;
  char buffer[LONG_STRING];
  const char *p;
  size_t i;

  dprint (2, (debugfile, "parse_parameters: `%s'\n", s));
  
  while (*s)
  {
    if ((p = strpbrk (s, "=;")) == NULL)
    {
      dprint(1, (debugfile, "parse_parameters: malformed parameter: %s\n", s));
      goto bail;
    }

    /* if we hit a ; now the parameter has no value, just skip it */
    if (*p != ';')
    {
      i = p - s;
      /* remove whitespace from the end of the attribute name */
      while (i > 0 && is_email_wsp(s[i-1]))
	--i;

      /* the check for the missing parameter token is here so that we can skip
       * over any quoted value that may be present.
       */
      if (i == 0)
      {
	dprint(1, (debugfile, "parse_parameters: missing attribute: %s\n", s));
	new = NULL;
      }
      else
      {
	new = mutt_new_parameter ();
	new->attribute = mutt_substrdup(s, s + i);
      }

      s = skip_email_wsp(p + 1); /* skip over the = */

      if (*s == '"')
      {
        int state_ascii = 1;
	s++;
	for (i=0; *s && i < sizeof (buffer) - 1; i++, s++)
	{
	  if (AssumedCharset && *AssumedCharset) {
            /* As iso-2022-* has a character of '"' with non-ascii state,
	     * ignore it. */
            if (*s == 0x1b && i < sizeof (buffer) - 2)
            {
              if (s[1] == '(' && (s[2] == 'B' || s[2] == 'J'))
                state_ascii = 1;
              else
                state_ascii = 0;
            }
          }
          if (state_ascii && *s == '"')
            break;
	  if (*s == '\\')
	  {
	    /* Quote the next character */
	    buffer[i] = s[1];
	    if (!*++s)
	      break;
	  }
	  else
	    buffer[i] = *s;
	}
	buffer[i] = 0;
	if (*s)
	  s++; /* skip over the " */
      }
      else
      {
	for (i=0; *s && *s != ' ' && *s != ';' && i < sizeof (buffer) - 1; i++, s++)
	  buffer[i] = *s;
	buffer[i] = 0;
      }

      /* if the attribute token was missing, 'new' will be NULL */
      if (new)
      {
	new->value = safe_strdup (buffer);

	dprint (2, (debugfile, "parse_parameter: `%s' = `%s'\n",
	      new->attribute ? new->attribute : "",
	      new->value ? new->value : ""));

	/* Add this parameter to the list */
	if (head)
	{
	  cur->next = new;
	  cur = cur->next;
	}
	else
	  head = cur = new;
      }
    }
    else
    {
      dprint (1, (debugfile, "parse_parameters(): parameter with no value: %s\n", s));
      s = p;
    }

    /* Find the next parameter */
    if (*s != ';' && (s = strchr (s, ';')) == NULL)
      break; /* no more parameters */

    do
    {
      /* Move past any leading whitespace. the +1 skips over the semicolon */
      s = skip_email_wsp(s + 1);
    }
    while (*s == ';'); /* skip empty parameters */
  }    

bail:

  rfc2231_decode_parameters (&head);
  return (head);
}