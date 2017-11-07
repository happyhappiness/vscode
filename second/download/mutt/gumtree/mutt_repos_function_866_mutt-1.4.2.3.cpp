void mutt_save_attachment_list (FILE *fp, int tag, BODY *top, HEADER *hdr)
{
  char buf[_POSIX_PATH_MAX], tfile[_POSIX_PATH_MAX];
  int rc = 1;
  FILE *fpout;

  buf[0] = 0;

  for (; top; top = top->next)
  {
    if (!tag || top->tagged)
    {
      if (!option (OPTATTACHSPLIT))
      {
	if (!buf[0])
	{
	  int append = 0;

	  strfcpy (buf, NONULL (top->filename), sizeof (buf));
	  if (mutt_get_field (_("Save to file: "), buf, sizeof (buf),
				    M_FILE | M_CLEAR) != 0 || !buf[0])
	    return;
	  mutt_expand_path (buf, sizeof (buf));
	  if (mutt_check_overwrite (top->filename, buf, tfile,
				    sizeof (tfile), &append))
	    return;
	  rc = mutt_save_attachment (fp, top, tfile, append, hdr);
	  if (rc == 0 && AttachSep && (fpout = fopen (tfile,"a")) != NULL)
	  {
	    fprintf(fpout, "%s", AttachSep);
	    fclose (fpout);
	  }
	}
	else
	{
	  rc = mutt_save_attachment (fp, top, tfile, M_SAVE_APPEND, hdr);
	  if (rc == 0 && AttachSep && (fpout = fopen (tfile,"a")) != NULL)
	  {
	    fprintf(fpout, "%s", AttachSep);
	    fclose (fpout);
	  }
	}
      }
      else
	mutt_query_save_attachment (fp, top, hdr);
    }
    else if (top->parts)
      mutt_save_attachment_list (fp, 1, top->parts, hdr);
    if (!tag)
      return;
  }

  if (!option (OPTATTACHSPLIT) && (rc == 0))
    mutt_message _("Attachment saved.");
}