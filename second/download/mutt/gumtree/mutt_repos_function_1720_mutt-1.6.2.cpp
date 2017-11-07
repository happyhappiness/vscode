BODY *pgp_make_key_attachment (char *tempf)
{
  BODY *att;
  char buff[LONG_STRING];
  char tempfb[_POSIX_PATH_MAX], tmp[STRING];
  FILE *tempfp;
  FILE *devnull;
  struct stat sb;
  pid_t thepid;
  pgp_key_t key;
  unset_option (OPTPGPCHECKTRUST);

  key = pgp_ask_for_key (_("Please enter the key ID: "), NULL, 0, PGP_PUBRING);

  if (!key)    return NULL;

  snprintf (tmp, sizeof (tmp), "0x%s", pgp_fpr_or_lkeyid (pgp_principal_key (key)));
  pgp_free_key (&key);

  if (!tempf)
  {
    mutt_mktemp (tempfb, sizeof (tempfb));
    tempf = tempfb;
  }

  if ((tempfp = safe_fopen (tempf, tempf == tempfb ? "w" : "a")) == NULL)
  {
    mutt_perror _("Can't create temporary file");
    return NULL;
  }

  if ((devnull = fopen ("/dev/null", "w")) == NULL)	/* __FOPEN_CHECKED__ */
  {
    mutt_perror _("Can't open /dev/null");
    safe_fclose (&tempfp);
    if (tempf == tempfb)
      unlink (tempf);
    return NULL;
  }

  mutt_message _("Invoking PGP...");


  if ((thepid = 
       pgp_invoke_export (NULL, NULL, NULL, -1,
			   fileno (tempfp), fileno (devnull), tmp)) == -1)
  {
    mutt_perror _("Can't create filter");
    unlink (tempf);
    safe_fclose (&tempfp);
    safe_fclose (&devnull);
    return NULL;
  }

  mutt_wait_filter (thepid);

  safe_fclose (&tempfp);
  safe_fclose (&devnull);

  att = mutt_new_body ();
  att->filename = safe_strdup (tempf);
  att->unlink = 1;
  att->use_disp = 0;
  att->type = TYPEAPPLICATION;
  att->subtype = safe_strdup ("pgp-keys");
  snprintf (buff, sizeof (buff), _("PGP Key %s."), tmp);
  att->description = safe_strdup (buff);
  mutt_update_encoding (att);

  stat (tempf, &sb);
  att->length = sb.st_size;

  return att;
}