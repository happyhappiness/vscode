void mutt_parse_content_type (char *s, BODY *ct)
{
  char *pc;
  char *subtype;

  FREE (&ct->subtype);
  mutt_free_parameter(&ct->parameter);

  /* First extract any existing parameters */
  if ((pc = strchr(s, ';')) != NULL)
  {
    *pc++ = 0;
    while (*pc && ISSPACE (*pc))
      pc++;
    ct->parameter = parse_parameters(pc);

    /* Some pre-RFC1521 gateways still use the "name=filename" convention,
     * but if a filename has already been set in the content-disposition,
     * let that take precedence, and don't set it here */
    if ((pc = mutt_get_parameter( "name", ct->parameter)) && !ct->filename)
      ct->filename = safe_strdup(pc);
    
#ifdef SUN_ATTACHMENT
    /* this is deep and utter perversion */
    if ((pc = mutt_get_parameter ("conversions", ct->parameter)))
      ct->encoding = mutt_check_encoding (pc);
#endif
    
  }
  
  /* Now get the subtype */
  if ((subtype = strchr(s, '/')))
  {
    *subtype++ = '\0';
    for(pc = subtype; *pc && !ISSPACE(*pc) && *pc != ';'; pc++)
      ;
    *pc = '\0';
    ct->subtype = safe_strdup (subtype);
  }

  /* Finally, get the major type */
  ct->type = mutt_check_mime_type (s);

#ifdef SUN_ATTACHMENT
  if (ascii_strcasecmp ("x-sun-attachment", s) == 0)
      ct->subtype = safe_strdup ("x-sun-attachment");
#endif

  if (ct->type == TYPEOTHER)
  {
    ct->xtype = safe_strdup (s);
  }

  if (ct->subtype == NULL)
  {
    /* Some older non-MIME mailers (i.e., mailtool, elm) have a content-type
     * field, so we can attempt to convert the type to BODY here.
     */
    if (ct->type == TYPETEXT)
      ct->subtype = safe_strdup ("plain");
    else if (ct->type == TYPEAUDIO)
      ct->subtype = safe_strdup ("basic");
    else if (ct->type == TYPEMESSAGE)
      ct->subtype = safe_strdup ("rfc822");
    else if (ct->type == TYPEOTHER)
    {
      char buffer[SHORT_STRING];

      ct->type = TYPEAPPLICATION;
      snprintf (buffer, sizeof (buffer), "x-%s", s);
      ct->subtype = safe_strdup (buffer);
    }
    else
      ct->subtype = safe_strdup ("x-unknown");
  }

  /* Default character set for text types. */
  if (ct->type == TYPETEXT)
  {
    if (!(pc = mutt_get_parameter ("charset", ct->parameter)))
      mutt_set_parameter ("charset", (AssumedCharset && *AssumedCharset) ?
                         (const char *) mutt_get_default_charset ()
                         : "us-ascii", &ct->parameter);
  }

}