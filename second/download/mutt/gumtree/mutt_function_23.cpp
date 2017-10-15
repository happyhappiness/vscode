void mutt_body_handler (BODY *b, STATE *s)
{
  int decode = 0;
  int plaintext = 0;
  FILE *fp = NULL;
  char tempfile[_POSIX_PATH_MAX];
  handler_t handler = NULL;
  long tmpoffset = 0;
  size_t tmplength = 0;
  char type[STRING];

  int oflags = s->flags;
  
  /* first determine which handler to use to process this part */

  snprintf (type, sizeof (type), "%s/%s", TYPE (b), b->subtype);
  if (mutt_is_autoview (b, type))
  {
    rfc1524_entry *entry = rfc1524_new_entry ();

    if (rfc1524_mailcap_lookup (b, type, entry, M_AUTOVIEW))
    {
      handler   = autoview_handler;
      s->flags &= ~M_CHARCONV;
    }
    rfc1524_free_entry (&entry);
  }
  else if (b->type == TYPETEXT)
  {
    if (ascii_strcasecmp ("plain", b->subtype) == 0)
    {
      /* avoid copying this part twice since removing the transfer-encoding is
       * the only operation needed.
       */
      if (ascii_strcasecmp ("flowed", mutt_get_parameter ("format", b->parameter)) == 0)
	handler = text_plain_flowed_handler;
      else
	plaintext = 1;
    }
    else if (ascii_strcasecmp ("enriched", b->subtype) == 0)
      handler = text_enriched_handler;
    else if (ascii_strcasecmp ("rfc822-headers", b->subtype) == 0)
      plaintext = 1;
  }
  else if (b->type == TYPEMESSAGE)
  {
    if(mutt_is_message_type(b->type, b->subtype))
      handler = message_handler;
    else if (!ascii_strcasecmp ("delivery-status", b->subtype))
      plaintext = 1;
    else if (!ascii_strcasecmp ("external-body", b->subtype))
      handler = external_body_handler;
  }
  else if (b->type == TYPEMULTIPART)
  {



#ifdef HAVE_PGP
    char *p;
#endif /* HAVE_PGP */



    if (ascii_strcasecmp ("alternative", b->subtype) == 0)
      handler = alternative_handler;



#ifdef HAVE_PGP
    else if (ascii_strcasecmp ("signed", b->subtype) == 0)
    {
      p = mutt_get_parameter ("protocol", b->parameter);

      if (!p)
        mutt_error _("Error: multipart/signed has no protocol.");
      else if (ascii_strcasecmp ("application/pgp-signature", p) == 0 ||
	       ascii_strcasecmp ("multipart/mixed", p) == 0)
      {
	if (s->flags & M_VERIFY)
	  handler = pgp_signed_handler;
      }
    }
    else if (ascii_strcasecmp ("encrypted", b->subtype) == 0)
    {
      p = mutt_get_parameter ("protocol", b->parameter);

      if (!p)
        mutt_error _("Error: multipart/encrypted has no protocol parameter!");
      else if (ascii_strcasecmp ("application/pgp-encrypted", p) == 0)
        handler = pgp_encrypted_handler;
    }
#endif /* HAVE_PGP */



    if (!handler)
      handler = multipart_handler;
  }



#ifdef HAVE_PGP
  else if (b->type == TYPEAPPLICATION)
  {
    if (mutt_is_application_pgp(b))
      handler = pgp_application_pgp_handler;
  }
#endif /* HAVE_PGP */



  if (plaintext || handler)
  {
    fseek (s->fpin, b->offset, 0);

    /* see if we need to decode this part before processing it */
    if (b->encoding == ENCBASE64 || b->encoding == ENCQUOTEDPRINTABLE ||
	b->encoding == ENCUUENCODED || plaintext || 
	mutt_is_text_type (b->type, b->subtype))	/* text subtypes may
							 * require character
							 * set conversion even
							 * with 8bit encoding.
							 */
    {
      int origType = b->type;
      char *savePrefix = NULL;

      if (!plaintext)
      {
	/* decode to a tempfile, saving the original destination */
	fp = s->fpout;
	mutt_mktemp (tempfile);
	if ((s->fpout = safe_fopen (tempfile, "w")) == NULL)
	{
	  mutt_error _("Unable to open temporary file!");
	  goto bail;
	}
	/* decoding the attachment changes the size and offset, so save a copy
	 * of the "real" values now, and restore them after processing
	 */
	tmplength = b->length;
	tmpoffset = b->offset;

	/* if we are decoding binary bodies, we don't want to prefix each
	 * line with the prefix or else the data will get corrupted.
	 */
	savePrefix = s->prefix;
	s->prefix = NULL;

	decode = 1;
      }
      else
	b->type = TYPETEXT;

      mutt_decode_attachment (b, s);

      if (decode)
      {
	b->length = ftell (s->fpout);
	b->offset = 0;
	fclose (s->fpout);

	/* restore final destination and substitute the tempfile for input */
	s->fpout = fp;
	fp = s->fpin;
	s->fpin = fopen (tempfile, "r");
	unlink (tempfile);

	/* restore the prefix */
	s->prefix = savePrefix;
      }

      b->type = origType;
    }

    /* process the (decoded) body part */
    if (handler)
    {
      handler (b, s);

      if (decode)
      {
	b->length = tmplength;
	b->offset = tmpoffset;

	/* restore the original source stream */
	fclose (s->fpin);
	s->fpin = fp;
      }
    }
  }
  else if (s->flags & M_DISPLAY)
  {
    state_mark_attach (s);
    state_printf (s, _("[-- %s/%s is unsupported "), TYPE (b), b->subtype);
    if (!option (OPTVIEWATTACH))
    {
      if (km_expand_key (type, sizeof(type),
			km_find_func (MENU_PAGER, OP_VIEW_ATTACHMENTS)))
	fprintf (s->fpout, _("(use '%s' to view this part)"), type);
      else
	fputs (_("(need 'view-attachments' bound to key!)"), s->fpout);
    }
    fputs (" --]\n", s->fpout);
  }
  
  bail:
  s->flags = oflags;
}