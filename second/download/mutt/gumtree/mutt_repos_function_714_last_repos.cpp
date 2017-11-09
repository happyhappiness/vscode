static gpgme_data_t body_to_data_object (BODY *a, int convert)
{
  char tempfile[_POSIX_PATH_MAX];
  FILE *fptmp;
  int err = 0;
  gpgme_data_t data;
  
  mutt_mktemp (tempfile, sizeof (tempfile));
  fptmp = safe_fopen (tempfile, "w+");
  if (!fptmp)
    {
      mutt_perror (tempfile);
      return NULL;
    }

  mutt_write_mime_header (a, fptmp);
  fputc ('\n', fptmp);
  mutt_write_mime_body (a, fptmp);

  if (convert)
    {
      int c, hadcr = 0;
      unsigned char buf[1];

      data = create_gpgme_data ();
      rewind (fptmp);
      while ((c = fgetc (fptmp)) != EOF)
        {
          if  (c == '\r')
            hadcr = 1;
          else 
            {
              if (c == '\n' && !hadcr)
                {
                  buf[0] = '\r';
                  gpgme_data_write (data, buf, 1);
                }
                  
              hadcr = 0;
            }
          /* FIXME: This is quite suboptimal */
          buf[0] = c;
          gpgme_data_write (data, buf, 1);
        }
      safe_fclose (&fptmp);
      gpgme_data_seek (data, 0, SEEK_SET);
    }
  else
    {
      safe_fclose (&fptmp);
      err = gpgme_data_new_from_file (&data, tempfile, 1);
    }
  unlink (tempfile);
  if (err) 
    {
      mutt_error (_("error allocating data object: %s\n"), gpgme_strerror (err));
      return NULL;
    }

  return data;
}