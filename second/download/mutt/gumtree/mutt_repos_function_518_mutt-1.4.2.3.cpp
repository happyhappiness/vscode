int
_mutt_copy_message (FILE *fpout, FILE *fpin, HEADER *hdr, BODY *body,
		    int flags, int chflags)
{
  char prefix[SHORT_STRING];
  STATE s;
  long new_offset = -1;

  if (flags & M_CM_PREFIX)
  {
    if (option (OPTTEXTFLOWED))
      strfcpy (prefix, ">", sizeof (prefix));
    else
      _mutt_make_string (prefix, sizeof (prefix), NONULL (Prefix), Context, hdr, 0);
  }

  if ((flags & M_CM_NOHEADER) == 0)
  {
    if (flags & M_CM_PREFIX)
      chflags |= CH_PREFIX;

    else if (hdr->attach_del && (chflags & CH_UPDATE_LEN))
    {
      int new_lines;
      long new_length = body->length;
      char date[SHORT_STRING];

      mutt_make_date (date, sizeof (date));
      date[5] = date[mutt_strlen (date) - 1] = '\"';

      /* Count the number of lines and bytes to be deleted */
      fseek (fpin, body->offset, SEEK_SET);
      new_lines = hdr->lines -
	count_delete_lines (fpin, body, &new_length, mutt_strlen (date));

      /* Copy the headers */
      if (mutt_copy_header (fpin, hdr, fpout,
			    chflags | CH_NOLEN | CH_NONEWLINE, NULL))
	return -1;
      fprintf (fpout, "Content-Length: %ld\n", new_length);
      if (new_lines <= 0)
	new_lines = 0;
      else
	fprintf (fpout, "Lines: %d\n\n", new_lines);
      if (ferror (fpout) || feof (fpout))
	return -1;
      new_offset = ftell (fpout);

      /* Copy the body */
      fseek (fpin, body->offset, SEEK_SET);
      if (copy_delete_attach (body, fpin, fpout, date))
	return -1;

#ifdef DEBUG
      {
	long fail = ((ftell (fpout) - new_offset) - new_length);

	if (fail)
	{
	  mutt_error ("The length calculation was wrong by %ld bytes", fail);
	  new_length += fail;
	  mutt_sleep (1);
	}
      }
#endif

      /* Update original message if we are sync'ing a mailfolder */ 
      if (flags & M_CM_UPDATE)
      {
	hdr->attach_del = 0;
	hdr->lines = new_lines;
	body->offset = new_offset;
	body->length = new_length;
	mutt_free_body (&body->parts);
      }

      return 0;
    }

    if (mutt_copy_header (fpin, hdr, fpout, chflags,
			  (chflags & CH_PREFIX) ? prefix : NULL) == -1)
      return -1;

    new_offset = ftell (fpout);
  }

  if (flags & M_CM_DECODE)
  {
    /* now make a text/plain version of the message */
    memset (&s, 0, sizeof (STATE));
    s.fpin = fpin;
    s.fpout = fpout;
    if (flags & M_CM_PREFIX)
      s.prefix = prefix;
    if (flags & M_CM_DISPLAY)
      s.flags |= M_DISPLAY;
    if (flags & M_CM_PRINTING)
      s.flags |= M_PRINTING;
    if (flags & M_CM_WEED)
      s.flags |= M_WEED;
    if (flags & M_CM_CHARCONV)
      s.flags |= M_CHARCONV;
    
#ifdef HAVE_PGP
    if (flags & M_CM_VERIFY)
      s.flags |= M_VERIFY;
#endif

    mutt_body_handler (body, &s);
  }
#ifdef HAVE_PGP
  else if ((flags & M_CM_DECODE_PGP) && (hdr->pgp & PGPENCRYPT) &&
      hdr->content->type == TYPEMULTIPART)
  {
    BODY *cur;
    FILE *fp;

    if (pgp_decrypt_mime (fpin, &fp, hdr->content, &cur))
      return (-1);
    fputs ("Mime-Version: 1.0\n", fpout);
    mutt_write_mime_header (cur, fpout);
    fputc ('\n', fpout);

    fseek (fp, cur->offset, 0);
    if (mutt_copy_bytes (fp, fpout, cur->length) == -1)
    {
      fclose (fp);
      mutt_free_body (&cur);
      return (-1);
    }
    mutt_free_body (&cur);
    fclose (fp);
  }
#endif
  else
  {
    fseek (fpin, body->offset, 0);
    if (flags & M_CM_PREFIX)
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

  if ((flags & M_CM_UPDATE) && (flags & M_CM_NOHEADER) == 0 
      && new_offset != -1)
  {
    body->offset = new_offset;
    mutt_free_body (&body->parts);
  }

  return 0;
}