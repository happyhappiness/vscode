int mutt_lookup_mime_type (BODY *att, const char *path)
{
  FILE *f;
  char *p, *q, *ct;
  char buf[LONG_STRING];
  char subtype[STRING], xtype[STRING];
  int count;
  int szf, sze, cur_sze;
  int type;

  *subtype = '\0';
  *xtype   = '\0';
  type     = TYPEOTHER;
  cur_sze  = 0;

  szf      = mutt_strlen (path);

  for (count = 0 ; count < 3 ; count++)
  {
    /*
     * can't use strtok() because we use it in an inner loop below, so use
     * a switch statement here instead.
     */
    switch (count)
    {
      case 0:
	snprintf (buf, sizeof (buf), "%s/.mime.types", NONULL(Homedir));
	break;
      case 1:
	strfcpy (buf, SYSCONFDIR"/mime.types", sizeof(buf));
	break;
      case 2:
	strfcpy (buf, PKGDATADIR"/mime.types", sizeof (buf));
	break;
      default:
        dprint (1, (debugfile, "mutt_lookup_mime_type: Internal error, count = %d.\n", count));
	goto bye;	/* shouldn't happen */
    }

    if ((f = fopen (buf, "r")) != NULL)
    {
      while (fgets (buf, sizeof (buf) - 1, f) != NULL)
      {
	/* weed out any comments */
	if ((p = strchr (buf, '#')))
	  *p = 0;

	/* remove any leading space. */
	ct = buf;
	SKIPWS (ct);

	/* position on the next field in this line */
	if ((p = strpbrk (ct, " \t")) == NULL)
	  continue;
	*p++ = 0;
	SKIPWS (p);

	/* cycle through the file extensions */
	while ((p = strtok (p, " \t\n")))
	{
	  sze = mutt_strlen (p);
	  if ((sze > cur_sze) && (szf >= sze) &&
	      (mutt_strcasecmp (path + szf - sze, p) == 0 || ascii_strcasecmp (path + szf - sze, p) == 0) &&
	      (szf == sze || path[szf - sze - 1] == '.'))
	  {
	    /* get the content-type */

	    if ((p = strchr (ct, '/')) == NULL)
	    {
	      /* malformed line, just skip it. */
	      break;
	    }
	    *p++ = 0;

	    for (q = p; *q && !ISSPACE (*q); q++)
	      ;

	    mutt_substrcpy (subtype, p, q, sizeof (subtype));

	    if ((type = mutt_check_mime_type (ct)) == TYPEOTHER)
	      strfcpy (xtype, ct, sizeof (xtype));

	    cur_sze = sze;
	  }
	  p = NULL;
	}
      }
      safe_fclose (&f);
    }
  }

 bye:

  if (type != TYPEOTHER || *xtype != '\0')
  {
    att->type = type;
    mutt_str_replace (&att->subtype, subtype);
    mutt_str_replace (&att->xtype, xtype);
  }

  return (type);
}