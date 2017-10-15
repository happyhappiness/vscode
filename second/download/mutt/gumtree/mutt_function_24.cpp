int mutt_body_handler (BODY *b, STATE *s)
{
  int decode = 0;
  int plaintext = 0;
  FILE *fp = NULL;
  char tempfile[_POSIX_PATH_MAX];
  handler_t handler = NULL;
  long tmpoffset = 0;
  size_t tmplength = 0;
  int rc = 0;

  int oflags = s->flags;
  
  /* first determine which handler to use to process this part */

  if (mutt_is_autoview (b))
  {
    handler = autoview_handler;
    s->flags &= ~M_CHARCONV;
  }
  else if (b->type == TYPETEXT)
  {
    if (ascii_strcasecmp ("plain", b->subtype) == 0)
    {
      /* avoid copying this part twice since removing the transfer-encoding is
       * the only operation needed.
       */
      if ((WithCrypto & APPLICATION_PGP) && mutt_is_application_pgp (b))
	handler = crypt_pgp_application_pgp_handler;
      else if (option(OPTREFLOWTEXT) && ascii_strcasecmp ("flowed", mutt_get_parameter ("format", b->parameter)) == 0)
	handler = rfc3676_handler;
      else
	handler = text_plain_handler;
    }
    else if (ascii_strcasecmp ("enriched", b->subtype) == 0)
      handler = text_enriched_handler;
    else /* text body type without a handler */
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
    char *p;

    if (ascii_strcasecmp ("alternative", b->subtype) == 0)
      handler = alternative_handler;
    else if (WithCrypto && ascii_strcasecmp ("signed", b->subtype) == 0)
    {
      p = mutt_get_parameter ("protocol", b->parameter);

      if (!p)
        mutt_error _("Error: multipart/signed has no protocol.");
      else if (s->flags & M_VERIFY)
	handler = mutt_signed_handler;
    }
    else if ((WithCrypto & APPLICATION_PGP)
             && ascii_strcasecmp ("encrypted", b->subtype) == 0)
    {
      p = mutt_get_parameter ("protocol", b->parameter);

      if (!p)
        mutt_error _("Error: multipart/encrypted has no protocol parameter!");
      else if (ascii_strcasecmp ("application/pgp-encrypted", p) == 0)
        handler = crypt_pgp_encrypted_handler;
    }

    if (!handler)
      handler = multipart_handler;
    
    if (b->encoding != ENC7BIT && b->encoding != ENC8BIT
        && b->encoding != ENCBINARY)
    {
      dprint (1, (debugfile, "Bad encoding type %d for multipart entity, "
                  "assuming 7 bit\n", b->encoding));
      b->encoding = ENC7BIT;
    }
  }
  else if (WithCrypto && b->type == TYPEAPPLICATION)
  {
    if (option (OPTDONTHANDLEPGPKEYS)
        && !ascii_strcasecmp("pgp-keys", b->subtype))
    {
      /* pass raw part through for key extraction */
      plaintext = 1;
    }
    else if ((WithCrypto & APPLICATION_PGP) && mutt_is_application_pgp (b))
      handler = crypt_pgp_application_pgp_handler;
    else if ((WithCrypto & APPLICATION_SMIME) && mutt_is_application_smime(b))
      handler = crypt_smime_application_smime_handler;
  }

  /* only respect disposition == attachment if we're not
     displaying from the attachment menu (i.e. pager) */
  if ((!option (OPTHONORDISP) || (b->disposition != DISPATTACH ||
				  option(OPTVIEWATTACH))) &&
       (plaintext || handler))
  {
    fseeko (s->fpin, b->offset, 0);

    /* see if we need to decode this part before processing it */
    if (b->encoding == ENCBASE64 || b->encoding == ENCQUOTEDPRINTABLE ||
	b->encoding == ENCUUENCODED || plaintext || 
	mutt_is_text_part (b))				/* text subtypes may
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
	mutt_mktemp (tempfile, sizeof (tempfile));
	if ((s->fpout = safe_fopen (tempfile, "w")) == NULL)
	{
	  mutt_error _("Unable to open temporary file!");
	  dprint (1, (debugfile, "Can't open %s.\n", tempfile));
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
	b->length = ftello (s->fpout);
	b->offset = 0;
	safe_fclose (&s->fpout);

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
      rc = handler (b, s);

      if (rc)
      {
	dprint (1, (debugfile, "Failed on attachment of type %s/%s.\n", TYPE(b), NONULL (b->subtype)));
      }
      
      if (decode)
      {
	b->length = tmplength;
	b->offset = tmpoffset;

	/* restore the original source stream */
	safe_fclose (&s->fpin);
	s->fpin = fp;
      }
    }
    s->flags |= M_FIRSTDONE;
  }
  /* print hint to use attachment menu for disposition == attachment
     if we're not already being called from there */
  else if ((s->flags & M_DISPLAY) || (b->disposition == DISPATTACH &&
				      !option (OPTVIEWATTACH) &&
				      option (OPTHONORDISP) &&
				      (plaintext || handler)))
  {
    state_mark_attach (s);
    if (option (OPTHONORDISP) && b->disposition == DISPATTACH)
      fputs (_("[-- This is an attachment "), s->fpout);
    else
      state_printf (s, _("[-- %s/%s is unsupported "), TYPE (b), b->subtype);
    if (!option (OPTVIEWATTACH))
    {
      char keystroke[SHORT_STRING];

      if (km_expand_key (keystroke, sizeof(keystroke),
			km_find_func (MENU_PAGER, OP_VIEW_ATTACHMENTS)))
	fprintf (s->fpout, _("(use '%s' to view this part)"), keystroke);
      else
	fputs (_("(need 'view-attachments' bound to key!)"), s->fpout);
    }
    fputs (" --]\n", s->fpout);
  }

  bail:
  s->flags = oflags | (s->flags & M_FIRSTDONE);
  if (rc)
  {
    dprint (1, (debugfile, "Bailing on attachment of type %s/%s.\n", TYPE(b), NONULL (b->subtype)));
  }

  return rc;
}