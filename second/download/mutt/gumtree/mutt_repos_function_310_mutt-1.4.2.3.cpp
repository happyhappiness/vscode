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

      new = mutt_new_parameter ();

      new->attribute = safe_malloc (i + 1);
      memcpy (new->attribute, s, i);
      new->attribute[i] = 0;

      /* remove whitespace from the end of the attribute name */
      while (ISSPACE (new->attribute[--i]))
	new->attribute[i] = 0;

      s = p + 1; /* skip over the = */
      SKIPWS (s);

      if (*s == '"')
      {
	s++;
	for (i=0; *s && *s != '"' && i < sizeof (buffer) - 1; i++, s++)
	{
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
      s++;

      /* Move past any leading whitespace */
      SKIPWS (s);
    }
    while (*s == ';'); /* skip empty parameters */
  }    

  bail:

  rfc2231_decode_parameters (&head);
  return (head);
}