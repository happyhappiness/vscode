void mutt_edit_content_type (HEADER *h, BODY *b, FILE *fp)
{
  char buf[LONG_STRING];
  char obuf[LONG_STRING];
  char tmp[STRING];
  PARAMETER *p;

  char charset[STRING];
  char *cp;

  short charset_changed = 0;
  short type_changed = 0;
  
  cp = mutt_get_parameter ("charset", b->parameter);
  strfcpy (charset, NONULL (cp), sizeof (charset));

  snprintf (buf, sizeof (buf), "%s/%s", TYPE (b), b->subtype);
  strfcpy (obuf, buf, sizeof (obuf));
  if (b->parameter)
  {
    size_t l;
    
    for (p = b->parameter; p; p = p->next)
    {
      l = strlen (buf);

      rfc822_cat (tmp, sizeof (tmp), p->value, MimeSpecials);
      snprintf (buf + l, sizeof (buf) - l, "; %s=%s", p->attribute, tmp);
    }
  }
  
  if (mutt_get_field ("Content-Type: ", buf, sizeof (buf), 0) != 0 ||
      buf[0] == 0)
    return;
  
  /* clean up previous junk */
  mutt_free_parameter (&b->parameter);
  FREE (&b->subtype);
  
  mutt_parse_content_type (buf, b);

  
  snprintf (tmp, sizeof (tmp), "%s/%s", TYPE (b), NONULL (b->subtype));
  type_changed = ascii_strcasecmp (tmp, obuf);
  charset_changed = ascii_strcasecmp (charset, mutt_get_parameter ("charset", b->parameter));

  /* if in send mode, check for conversion - current setting is default. */

  if (!h && b->type == TYPETEXT && charset_changed)
  {
    int r;
    snprintf (tmp, sizeof (tmp), _("Convert to %s upon sending?"),
	      mutt_get_parameter ("charset", b->parameter));
    if ((r = mutt_yesorno (tmp, !b->noconv)) != -1)
      b->noconv = (r == MUTT_NO);
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
  {
    b->hdr->content = NULL;
    mutt_free_header (&b->hdr);
  }

  if (fp && (is_multipart (b) || mutt_is_message_type (b->type, b->subtype)))
    mutt_parse_part (fp, b);
  
  if (WithCrypto && h)
  {
    if (h->content == b)
      h->security  = 0;

    h->security |= crypt_query (b);
  }
}