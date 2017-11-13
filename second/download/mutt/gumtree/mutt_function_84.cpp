void mutt_message_to_7bit (BODY *a, FILE *fp)
{
  char temp[_POSIX_PATH_MAX];
  char *line = NULL;
  FILE *fpin = NULL;
  FILE *fpout = NULL;
  struct stat sb;

  if (!a->filename && fp)
    fpin = fp;
  else if (!a->filename || !(fpin = fopen (a->filename, "r")))
  {
    mutt_error (_("Could not open %s"), a->filename ? a->filename : "(null)");
    return;
  } 
  else
  {
    a->offset = 0;
    if (stat (a->filename, &sb) == -1)
    {
      mutt_perror ("stat");
      fclose (fpin);
    }
    a->length = sb.st_size;
  }

  mutt_mktemp (temp);
  if (!(fpout = safe_fopen (temp, "w+")))
  {
    mutt_perror ("fopen");
    goto cleanup;
  }

  fseek (fpin, a->offset, 0);
  a->parts = mutt_parse_messageRFC822 (fpin, a);

  transform_to_7bit (a->parts, fpin);
  
  mutt_copy_hdr (fpin, fpout, a->offset, a->offset + a->length, 
		 CH_MIME | CH_NONEWLINE | CH_XMIT, NULL);

  fputs ("Mime-Version: 1.0\n", fpout);
  mutt_write_mime_header (a->parts, fpout);
  fputc ('\n', fpout);
  mutt_write_mime_body (a->parts, fpout);
  
 cleanup:
  safe_free ((void **) &line);

  if (fpin && !fp)
    fclose (fpin);
  if (fpout)
    fclose (fpout);
  else
    return;
  
  a->encoding = ENC7BIT;
  a->d_filename = a->filename;
  if (a->filename && a->unlink)
    unlink (a->filename);
  a->filename = safe_strdup (temp);
  a->unlink = 1;
  if(stat (a->filename, &sb) == -1) 
  {
    mutt_perror ("stat");
    return;
  }
  a->length = sb.st_size;
  mutt_free_body (&a->parts);
  a->hdr->content = NULL;
}