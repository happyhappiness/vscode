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
