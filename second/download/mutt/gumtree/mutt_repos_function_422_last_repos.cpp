static char *smime_extract_certificate (char *infile)
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

  mutt_mktemp (pk7out, sizeof (pk7out));
  if ((fpout = safe_fopen (pk7out, "w+")) == NULL)
  {
    safe_fclose (&fperr);
    mutt_perror (pk7out);
    return NULL;
  }

  /* Step 1: Convert the signature to a PKCS#7 structure, as we can't
     extract the full set of certificates directly.
  */
  if ((thepid =  smime_invoke (NULL, NULL, NULL,
			       -1, fileno (fpout), fileno (fperr),
			       infile, NULL, NULL, NULL, NULL, NULL, NULL,
			       SmimePk7outCommand))== -1)
  {
    mutt_any_key_to_continue (_("Error: unable to create OpenSSL subprocess!"));
    safe_fclose (&fperr);
    safe_fclose (&fpout);
    mutt_unlink (pk7out);
    return NULL;
  }

  mutt_wait_filter (thepid);


  fflush (fpout);
  rewind (fpout);
  fflush (fperr);
  rewind (fperr);
  empty = (fgetc (fpout) == EOF);
  if (empty)
  {
    mutt_perror (pk7out);
    mutt_copy_stream (fperr, stdout);
    safe_fclose (&fpout);
    safe_fclose (&fperr);
    mutt_unlink (pk7out);
    return NULL;
    
  }


  safe_fclose (&fpout);
  mutt_mktemp (certfile, sizeof (certfile));
  if ((fpout = safe_fopen (certfile, "w+")) == NULL)
  {
    safe_fclose (&fperr);
    mutt_unlink (pk7out);
    mutt_perror (certfile);
    return NULL;
  }
  
  /* Step 2: Extract the certificates from a PKCS#7 structure.
   */
  if ((thepid =  smime_invoke (NULL, NULL, NULL,
			       -1, fileno (fpout), fileno (fperr),
			       pk7out, NULL, NULL, NULL, NULL, NULL, NULL,
			       SmimeGetCertCommand))== -1)
  {
    mutt_any_key_to_continue (_("Error: unable to create OpenSSL subprocess!"));
    safe_fclose (&fperr);
    safe_fclose (&fpout);
    mutt_unlink (pk7out);
    mutt_unlink (certfile);
    return NULL;
  }

  mutt_wait_filter (thepid);

  mutt_unlink (pk7out);

  fflush (fpout);
  rewind (fpout);
  fflush (fperr);
  rewind (fperr);
  empty =  (fgetc (fpout) == EOF);
  if (empty)
  {
    mutt_copy_stream (fperr, stdout);
    safe_fclose (&fpout);
    safe_fclose (&fperr);
    mutt_unlink (certfile);
    return NULL;
  }

  safe_fclose (&fpout);
  safe_fclose (&fperr);

  return safe_strdup (certfile);
}