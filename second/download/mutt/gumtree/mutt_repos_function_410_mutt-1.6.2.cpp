static int smime_handle_cert_email (char *certificate, char *mailbox,
				   int copy, char ***buffer, int *num)
{
  FILE *fpout = NULL, *fperr = NULL;
  char tmpfname[_POSIX_PATH_MAX];
  char email[STRING];
  int ret = -1, count = 0;
  pid_t thepid;
  size_t len = 0;

  mutt_mktemp (tmpfname, sizeof (tmpfname));
  if ((fperr = safe_fopen (tmpfname, "w+")) == NULL)
  {
    mutt_perror (tmpfname);
    return 1;
  }
  mutt_unlink (tmpfname);

  mutt_mktemp (tmpfname, sizeof (tmpfname));
  if ((fpout = safe_fopen (tmpfname, "w+")) == NULL)
  {
    safe_fclose (&fperr);
    mutt_perror (tmpfname);
    return 1;
  }
  mutt_unlink (tmpfname);

  if ((thepid =  smime_invoke (NULL, NULL, NULL,
			       -1, fileno (fpout), fileno (fperr),
			       certificate, NULL, NULL, NULL, NULL, NULL, NULL,
			       SmimeGetCertEmailCommand))== -1)
  {
    mutt_message (_("Error: unable to create OpenSSL subprocess!"));
    safe_fclose (&fperr);
    safe_fclose (&fpout);
    return 1;
  }

  mutt_wait_filter (thepid);

  fflush (fpout);
  rewind (fpout);
  fflush (fperr);
  rewind (fperr);


  while ((fgets (email, sizeof (email), fpout)))
  {
    len = mutt_strlen (email);
    if (len && (email[len - 1] == '\n'))
      email[len - 1] = '\0';
    if(mutt_strncasecmp (email, mailbox, mutt_strlen (mailbox)) == 0)
      ret=1;

    ret = ret < 0 ? 0 : ret;
    count++;
  }

  if (ret == -1)
  {
    mutt_endwin(NULL);
    mutt_copy_stream (fperr, stdout);
    mutt_any_key_to_continue (_("Error: unable to create OpenSSL subprocess!"));
    ret = 1;
  }
  else if (!ret)
    ret = 1;
  else ret = 0;

  if(copy && buffer && num)
  {
    (*num) = count;
    *buffer =  safe_calloc(sizeof(char*), count);
    count = 0;

    rewind (fpout);
    while ((fgets (email, sizeof (email), fpout)))
    {
      len = mutt_strlen (email);
      if (len && (email[len - 1] == '\n'))
        email[len - 1] = '\0';
      (*buffer)[count] = safe_calloc(1, mutt_strlen (email) + 1);
      strncpy((*buffer)[count], email, mutt_strlen (email));
      count++;
    }
  }
  else if(copy) ret = 2;

  safe_fclose (&fpout);
  safe_fclose (&fperr);

  return ret;
}