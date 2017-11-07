static int mutt_query_save_attachment (FILE *fp, BODY *body, HEADER *hdr, char **directory)
{
  char *prompt;
  char buf[_POSIX_PATH_MAX], tfile[_POSIX_PATH_MAX];
  int is_message;
  int append = 0;
  int rc;
  
  if (body->filename) 
  {
    if (directory && *directory)
      mutt_concat_path (buf, *directory, mutt_basename (body->filename), sizeof (buf));
    else
      strfcpy (buf, body->filename, sizeof (buf));
  }
  else if(body->hdr &&
	  body->encoding != ENCBASE64 &&
	  body->encoding != ENCQUOTEDPRINTABLE &&
	  mutt_is_message_type(body->type, body->subtype))
    mutt_default_save(buf, sizeof(buf), body->hdr);
  else
    buf[0] = 0;

  prepend_curdir (buf, sizeof (buf));

  prompt = _("Save to file: ");
  while (prompt)
  {
    if (mutt_get_field (prompt, buf, sizeof (buf), MUTT_FILE | MUTT_CLEAR) != 0
	|| !buf[0])
    {
      mutt_clear_error ();
      return -1;
    }
    
    prompt = NULL;
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
      if ((rc = mutt_save_confirm (buf, &st)) == 1)
      {
	prompt = _("Save to file: ");
	continue;
      } 
      else if (rc == -1)
	return -1;
      strfcpy(tfile, buf, sizeof(tfile));
    }
    else
    {
      if ((rc = mutt_check_overwrite (body->filename, buf, tfile, sizeof (tfile), &append, directory)) == -1)
	return -1;
      else if (rc == 1)
      {
	prompt = _("Save to file: ");
	continue;
      }
    }
    
    mutt_message _("Saving...");
    if (mutt_save_attachment (fp, body, tfile, append, (hdr || !is_message) ? hdr : body->hdr) == 0)
    {
      mutt_message _("Attachment saved.");
      return 0;
    }
    else
    {
      prompt = _("Save to file: ");
      continue;
    }
  }
  return 0;
}