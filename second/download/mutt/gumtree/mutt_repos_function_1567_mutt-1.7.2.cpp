int mutt_is_application_smime (BODY *m)
{
  char *t=NULL;
  int len, complain=0;

  if(!m)
    return 0;

  if ((m->type & TYPEAPPLICATION) && m->subtype)
  {
    /* S/MIME MIME types don't need x- anymore, see RFC2311 */
    if (!ascii_strcasecmp (m->subtype, "x-pkcs7-mime") ||
	!ascii_strcasecmp (m->subtype, "pkcs7-mime"))
    {
      if ((t = mutt_get_parameter ("smime-type", m->parameter)))
      {
	if (!ascii_strcasecmp (t, "enveloped-data"))
	  return SMIMEENCRYPT;
	else if (!ascii_strcasecmp (t, "signed-data"))
	  return (SMIMESIGN|SMIMEOPAQUE);
	else return 0;
      }
      /* Netscape 4.7 uses 
       * Content-Description: S/MIME Encrypted Message
       * instead of Content-Type parameter
       */
      if (!ascii_strcasecmp (m->description, "S/MIME Encrypted Message"))
	return SMIMEENCRYPT;
      complain = 1;
    }
    else if (ascii_strcasecmp (m->subtype, "octet-stream"))
      return 0;

    t = mutt_get_parameter ("name", m->parameter);

    if (!t) t = m->d_filename;
    if (!t) t = m->filename;
    if (!t) 
    {
      if (complain)
	mutt_message (_("S/MIME messages with no hints on content are unsupported."));
      return 0;
    }

    /* no .p7c, .p10 support yet. */

    len = mutt_strlen (t) - 4;
    if (len > 0 && *(t+len) == '.')
    {
      len++;
      if (!ascii_strcasecmp ((t+len), "p7m"))
#if 0
       return SMIMEENCRYPT;
#else
      /* Not sure if this is the correct thing to do, but 
         it's required for compatibility with Outlook */
       return (SMIMESIGN|SMIMEOPAQUE);
#endif
      else if (!ascii_strcasecmp ((t+len), "p7s"))
	return (SMIMESIGN|SMIMEOPAQUE);
    }
  }

  return 0;
}