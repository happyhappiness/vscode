  if (*pt == '=') /* abort if no var before the '=' */
    return 0;

  if (mutt_strncmp (buffer, "set", 3) == 0)
  {
    int idx;
    strfcpy (var, pt, sizeof (var));
    /* ignore the trailing '=' when comparing */
    var[mutt_strlen (var) - 1] = 0;
    if ((idx = mutt_option_index (var)) == -1) 
      return 0; /* no such variable. */
    else
    {
      char tmp [LONG_STRING], tmp2[LONG_STRING];
      char *s, *d;
      size_t dlen = buffer + len - pt - spaces;
      char *vals[] = { "no", "yes", "ask-no", "ask-yes" };

      tmp[0] = '\0';

      if ((DTYPE(MuttVars[idx].type) == DT_STR) || 
	  (DTYPE(MuttVars[idx].type) == DT_PATH) ||
	  (DTYPE(MuttVars[idx].type) == DT_RX))
      {
	strfcpy (tmp, NONULL (*((char **) MuttVars[idx].data)), sizeof (tmp));
	if (DTYPE (MuttVars[idx].type) == DT_PATH)
	  mutt_pretty_mailbox (tmp);
      }
      else if (DTYPE (MuttVars[idx].type) == DT_ADDR)
      {
	rfc822_write_address (tmp, sizeof (tmp), *((ADDRESS **) MuttVars[idx].data));
      }
      else if (DTYPE (MuttVars[idx].type) == DT_QUAD)
	strfcpy (tmp, vals[quadoption (MuttVars[idx].data)], sizeof (tmp));
      else if (DTYPE (MuttVars[idx].type) == DT_NUM)
	snprintf (tmp, sizeof (tmp), "%d", (*((short *) MuttVars[idx].data)));
      else if (DTYPE (MuttVars[idx].type) == DT_SORT)
      {
	const struct mapping_t *map;
	char *p;

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
	  default:
	    map = SortMethods;
	    break;
	}
	p = mutt_getnamebyvalue (*((short *) MuttVars[idx].data) & SORT_MASK, map);
	snprintf (tmp, sizeof (tmp), "%s%s%s",
		  (*((short *) MuttVars[idx].data) & SORT_REVERSE) ? "reverse-" : "",
		  (*((short *) MuttVars[idx].data) & SORT_LAST) ? "last-" : "",
		  p);
      }
      else if (DTYPE (MuttVars[idx].type) == DT_BOOL)
	strfcpy (tmp, option (MuttVars[idx].data) ? "yes" : "no", sizeof (tmp));
      else
	return 0;
      
      for (s = tmp, d = tmp2; *s && (d - tmp2) < sizeof (tmp2) - 2;)
      {
	if (*s == '\\' || *s == '"')
	  *d++ = '\\';
	*d++ = *s++;
      }
      *d = '\0';
      
      strfcpy (tmp, pt, sizeof (tmp));
      snprintf (pt, dlen, "%s\"%s\"", tmp, tmp2);
	  
      return 1;
    }
  }
  return 0;
}

char *mutt_getnamebyvalue (int val, const struct mapping_t *map)
{
  int i;

  for (i=0; map[i].name; i++)
    if (map[i].value == val)
      return (map[i].name);
