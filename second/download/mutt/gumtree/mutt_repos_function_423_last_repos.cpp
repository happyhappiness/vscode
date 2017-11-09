static char *smime_extract_signer_certificate (char *infile)
{
  FILE *fpout = NULL, *fperr = NULL;
  char pk7out[_POSIX_PATH_MAX], certfile[_POSIX_PATH_MAX];
  char tmpfname[_POSIX_PATH_MAX];
  pid_t thepid;
  int empty;


  mutt_mktemp (tmpfname, sizeof (tmpfname));
  if ((fperr = safe_fopen (tmpfname, "w+")) == NULL)
  {
    mutt_perror (tmpfname);
    return NULL;
  }
  mutt_unlink (tmpfname);


  mutt_mktemp (certfile, sizeof (certfile));
  if ((fpout = safe_fopen (certfile, "w+")) == NULL)
  {
    safe_fclose (&fperr);
    mutt_perror (certfile);
    return NULL;
  }
  
  /* Extract signer's certificate
   */
  if ((thepid =  smime_invoke (NULL, NULL, NULL,
			       -1, -1, fileno (fperr),
			       infile, NULL, NULL, NULL, NULL, certfile, NULL,
			       SmimeGetSignerCertCommand))== -1)
  {
    mutt_any_key_to_continue (_("Error: unable to create OpenSSL subprocess!"));
    safe_fclose (&fperr);
    safe_fclose (&fpout);
    mutt_unlink (pk7out);
    mutt_unlink (certfile);
    return NULL;
  }

  mutt_wait_filter (thepid);

  fflush (fpout);
  rewind (fpout);
  fflush (fperr);
  rewind (fperr);
  empty =  (fgetc (fpout) == EOF);
  if (empty)
  {
    mutt_endwin (NULL);
    mutt_copy_stream (fperr, stdout);
    mutt_any_key_to_continue (NULL);
    safe_fclose (&fpout);
    safe_fclose (&fperr);
    mutt_unlink (certfile);
    return NULL;
  }

  safe_fclose (&fpout);
  safe_fclose (&fperr);

  return safe_strdup (certfile);
}