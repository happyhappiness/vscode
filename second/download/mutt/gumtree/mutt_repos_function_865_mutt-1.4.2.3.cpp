static int mutt_query_save_attachment (FILE *fp, BODY *body, HEADER *hdr)
{
  char buf[_POSIX_PATH_MAX], tfile[_POSIX_PATH_MAX];
  int is_message;
  int append = 0;

  if (body->filename)
    strfcpy (buf, body->filename, sizeof (buf));
  else if(body->hdr &&
	  body->encoding != ENCBASE64 &&
	  body->encoding != ENCQUOTEDPRINTABLE &&
	  mutt_is_message_type(body->type, body->subtype))
    mutt_default_save(buf, sizeof(buf), body->hdr);
  else
    buf[0] = 0;

  if (mutt_get_field (_("Save to file: "), buf, sizeof (buf), M_FILE | M_CLEAR) != 0
      || !buf[0])
    return -1;

  mutt_expand_path (buf, sizeof (buf));

  is_message = (fp && 
      body->hdr && 
      body->encoding != ENCBASE64 && 
      body->encoding != ENCQUOTEDPRINTABLE && 
      mutt_is_message_type (body->type, body->subtype));
  
  if (is_message)
  {
    struct stat st;
    
    /* check to make sure that this file is really the one the user wants */
    if (!mutt_save_confirm (buf, &st))
      return -1;
    strfcpy(tfile, buf, sizeof(tfile));
  }
  else
    if (mutt_check_overwrite (body->filename, buf, tfile, sizeof (tfile), &append))
      return -1;

  mutt_message _("Saving...");
  if (mutt_save_attachment (fp, body, tfile, append, (hdr || !is_message) ? hdr : body->hdr) == 0)
  {
    mutt_message _("Attachment saved.");
    return 0;
  }
  else
    return -1;
}