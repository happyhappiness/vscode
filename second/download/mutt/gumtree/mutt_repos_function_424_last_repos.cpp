void smime_invoke_import (char *infile, char *mailbox)
{
  char tmpfname[_POSIX_PATH_MAX], *certfile = NULL, buf[STRING];
  FILE *smimein=NULL, *fpout = NULL, *fperr = NULL;
  pid_t thepid=-1;

  mutt_mktemp (tmpfname, sizeof (tmpfname));
  if ((fperr = safe_fopen (tmpfname, "w+")) == NULL)
  {
    mutt_perror (tmpfname);
    return;
  }
  mutt_unlink (tmpfname);

  mutt_mktemp (tmpfname, sizeof (tmpfname));
  if ((fpout = safe_fopen (tmpfname, "w+")) == NULL)
  {
    safe_fclose (&fperr);
    mutt_perror (tmpfname);
    return;
  }
  mutt_unlink (tmpfname);


  buf[0] = '\0';
  if (option (OPTASKCERTLABEL))
    mutt_get_field (_("Label for certificate: "), buf, sizeof (buf), 0);

  mutt_endwin (NULL);
  if ((certfile = smime_extract_certificate(infile)))
  {
    mutt_endwin (NULL);
  
    if ((thepid =  smime_invoke (&smimein, NULL, NULL,
				 -1, fileno(fpout), fileno(fperr),
				 certfile, NULL, NULL, NULL, NULL, NULL, NULL,
				 SmimeImportCertCommand))== -1)
    {
      mutt_message (_("Error: unable to create OpenSSL subprocess!"));
      return;
    }
    fputs (buf, smimein);
    fputc ('\n', smimein);
    safe_fclose (&smimein);

    mutt_wait_filter (thepid);
  
    mutt_unlink (certfile);
    FREE (&certfile);
  }

  fflush (fpout);
  rewind (fpout);
  fflush (fperr);
  rewind (fperr);

  mutt_copy_stream (fpout, stdout);
  mutt_copy_stream (fperr, stdout);

  safe_fclose (&fpout);
  safe_fclose (&fperr);

}