static void push_string (char *s)
{
  char *pp, *p = s + mutt_strlen (s) - 1;
  size_t l;
  int i, op = OP_NULL;

  while (p >= s)
  {
    /* if we see something like "<PageUp>", look to see if it is a real
       function name and return the corresponding value */
    if (*p == '>')
    {
      for (pp = p - 1; pp >= s && *pp != '<'; pp--)
	;
      if (pp >= s)
      {
	if ((i = parse_fkey (pp)) > 0)
	{
	  mutt_ungetch (KEY_F (i), 0);
	  p = pp - 1;
	  continue;
	}

	l = p - pp + 1;
	for (i = 0; KeyNames[i].name; i++)
	{
	  if (!ascii_strncasecmp (pp, KeyNames[i].name, l))
	    break;
	}
	if (KeyNames[i].name)
	{
	  /* found a match */
	  mutt_ungetch (KeyNames[i].value, 0);
	  p = pp - 1;
	  continue;
	}

	/* See if it is a valid command
	 * skip the '<' and the '>' when comparing */
	for (i = 0; Menus[i].name; i++)
	{
	  struct binding_t *binding = km_get_table (Menus[i].value);
	  if (binding)
	  {
	    op = get_op (binding, pp + 1, l - 2);
	    if (op != OP_NULL)
	      break;
	  }
	}

	if (op != OP_NULL)
	{
	  mutt_ungetch (0, op);
	  p = pp - 1;
	  continue;
	}
      }
    }
    mutt_ungetch (*p--, 0);
  }
}