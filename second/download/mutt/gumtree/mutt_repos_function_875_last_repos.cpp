int
_mutt_copy_message (FILE *fpout, FILE *fpin, HEADER *hdr, BODY *body,
		    int flags, int chflags)
{
  char prefix[SHORT_STRING];
  STATE s;
  LOFF_T new_offset = -1;
  int rc = 0;

  if (flags & MUTT_CM_PREFIX)
  {
    if (option (OPTTEXTFLOWED))
      strfcpy (prefix, ">", sizeof (prefix));
    else
      _mutt_make_string (prefix, sizeof (prefix), NONULL (Prefix), Context, hdr, 0);
  }

  if (hdr->xlabel_changed)
    chflags |= CH_UPDATE_LABEL;

  if ((flags & MUTT_CM_NOHEADER) == 0)
  {
    if (flags & MUTT_CM_PREFIX)
      chflags |= CH_PREFIX;

    else if (hdr->attach_del && (chflags & CH_UPDATE_LEN))
    {
      int new_lines;
      LOFF_T new_length = body->length;
      char date[SHORT_STRING];

      mutt_make_date (date, sizeof (date));
      date[5] = date[mutt_strlen (date) - 1] = '\"';

      /* Count the number of lines and bytes to be deleted */
      fseeko (fpin, body->offset, SEEK_SET);
      new_lines = hdr->lines -
	count_delete_lines (fpin, body, &new_length, mutt_strlen (date));

      /* Copy the headers */
      if (mutt_copy_header (fpin, hdr, fpout,
			    chflags | CH_NOLEN | CH_NONEWLINE, NULL))
	return -1;
      fprintf (fpout, "Content-Length: " OFF_T_FMT "\n", new_length);
      if (new_lines <= 0)
	new_lines = 0;
      else
	fprintf (fpout, "Lines: %d\n", new_lines);

      putc ('\n', fpout);
      if (ferror (fpout) || feof (fpout))
	return -1;
      new_offset = ftello (fpout);

      /* Copy the body */
      fseeko (fpin, body->offset, SEEK_SET);
      if (copy_delete_attach (body, fpin, fpout, date))
	return -1;

#ifdef DEBUG
      {
	LOFF_T fail = ((ftello (fpout) - new_offset) - new_length);

	if (fail)
	{
	  mutt_error ("The length calculation was wrong by %ld bytes", fail);
	  new_length += fail;
	  mutt_sleep (1);
	}
      }
#endif

      /* Update original message if we are sync'ing a mailfolder */ 
      if (flags & MUTT_CM_UPDATE)
      {
	hdr->attach_del = 0;
	hdr->lines = new_lines;
	body->offset = new_offset;

	/* update the total size of the mailbox to reflect this deletion */
	Context->size -= body->length - new_length;
	/*
	 * if the message is visible, update the visible size of the mailbox
	 * as well.
	 */
	if (Context->v2r[hdr->msgno] != -1)
	  Context->vsize -= body->length - new_length;

	body->length = new_length;
	mutt_free_body (&body->parts);
      }

      return 0;
    }

    if (mutt_copy_header (fpin, hdr, fpout, chflags,
			  (chflags & CH_PREFIX) ? prefix : NULL) == -1)
      return -1;

    new_offset = ftello (fpout);
  }

  if (flags & MUTT_CM_DECODE)
  {
    /* now make a text/plain version of the message */
    memset (&s, 0, sizeof (STATE));
    s.fpin = fpin;
    s.fpout = fpout;
    if (flags & MUTT_CM_PREFIX)
      s.prefix = prefix;
    if (flags & MUTT_CM_DISPLAY)
      s.flags |= MUTT_DISPLAY;
    if (flags & MUTT_CM_PRINTING)
      s.flags |= MUTT_PRINTING;
    if (flags & MUTT_CM_WEED)
      s.flags |= MUTT_WEED;
    if (flags & MUTT_CM_CHARCONV)
      s.flags |= MUTT_CHARCONV;
    if (flags & MUTT_CM_REPLYING)
      s.flags |= MUTT_REPLYING;
    
    if (WithCrypto && flags & MUTT_CM_VERIFY)
      s.flags |= MUTT_VERIFY;

    rc = mutt_body_handler (body, &s);
  }
  else if (WithCrypto
           && (flags & MUTT_CM_DECODE_CRYPT) && (hdr->security & ENCRYPT))
  {
    BODY *cur = NULL;
    FILE *fp;

    if ((WithCrypto & APPLICATION_PGP)
        && (flags & MUTT_CM_DECODE_PGP) && (hdr->security & APPLICATION_PGP) &&
	hdr->content->type == TYPEMULTIPART)
    {
      if (crypt_pgp_decrypt_mime (fpin, &fp, hdr->content, &cur))
	return (-1);
      fputs ("MIME-Version: 1.0\n", fpout);
    }

    if ((WithCrypto & APPLICATION_SMIME)
        && (flags & MUTT_CM_DECODE_SMIME) && (hdr->security & APPLICATION_SMIME)
	     && hdr->content->type == TYPEAPPLICATION)
    {
      if (crypt_smime_decrypt_mime (fpin, &fp, hdr->content, &cur))
	return (-1);
    }

    if (!cur)
    {
      mutt_error (_("No decryption engine available for message"));
      return -1;
    }

    mutt_write_mime_header (cur, fpout);
    fputc ('\n', fpout);

    fseeko (fp, cur->offset, 0);
    if (mutt_copy_bytes (fp, fpout, cur->length) == -1)
    {
      safe_fclose (&fp);
      mutt_free_body (&cur);
      return (-1);
    }
    mutt_free_body (&cur);
    safe_fclose (&fp);
  }
  else
  {
    fseeko (fpin, body->offset, 0);
    if (flags & MUTT_CM_PREFIX)
    {
      int c;
      size_t bytes = body->length;
      
      fputs(prefix, fpout);
      
      while((c = fgetc(fpin)) != EOF && bytes--)
      {
	fputc(c, fpout);
	if(c == '\n')
	{
	  fputs(prefix, fpout);
	}
      } 
    }
    else if (mutt_copy_bytes (fpin, fpout, body->length) == -1)
      return -1;
  }

  if ((flags & MUTT_CM_UPDATE) && (flags & MUTT_CM_NOHEADER) == 0 
      && new_offset != -1)
  {
    body->offset = new_offset;
    mutt_free_body (&body->parts);
  }

  return rc;
}