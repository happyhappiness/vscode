  charset_changed = ascii_strcasecmp (charset, mutt_get_parameter ("charset", b->parameter));

  /* if in send mode, check for conversion - current setting is default. */

  if (!h && b->type == TYPETEXT && charset_changed)
  {
    int r;
    snprintf (tmp, sizeof (tmp), _("Convert to %s upon sending?"),
	      mutt_get_parameter ("charset", b->parameter));
    if ((r = mutt_yesorno (tmp, !b->noconv)) != -1)
      b->noconv = (r == M_NO);
  }

  /* inform the user */
  
  snprintf (tmp, sizeof (tmp), "%s/%s", TYPE (b), NONULL (b->subtype));
  if (type_changed)
    mutt_message (_("Content-Type changed to %s."), tmp);
  if (b->type == TYPETEXT && charset_changed)
  {
    if (type_changed)
      mutt_sleep (1);
    mutt_message (_("Character set changed to %s; %s."),
		  mutt_get_parameter ("charset", b->parameter),
		  b->noconv ? _("not converting") : _("converting"));
  }

  b->force_charset |= charset_changed ? 1 : 0;

  if (!is_multipart (b) && b->parts)
    mutt_free_body (&b->parts);
  if (!mutt_is_message_type (b->type, b->subtype) && b->hdr)
