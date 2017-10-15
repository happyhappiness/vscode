static void 
verify_key (crypt_key_t *key)
{
  FILE *fp;
  char cmd[LONG_STRING], tempfile[_POSIX_PATH_MAX];
  const char *s;
  gpgme_ctx_t listctx = NULL;
  gpgme_error_t err;
  gpgme_key_t k = NULL;
  int maxdepth = 100;

  mutt_mktemp (tempfile, sizeof (tempfile));
  if (!(fp = safe_fopen (tempfile, "w")))
    {
      mutt_perror _("Can't create temporary file");
      return;
    }
  mutt_message _("Collecting data...");

  print_key_info (key->kobj, fp);

  err = gpgme_new (&listctx);
  if (err)
    {
      fprintf (fp, "Internal error: can't create gpgme context: %s\n",
               gpgme_strerror (err));
      goto leave;
    }
  if ((key->flags & KEYFLAG_ISX509))
      gpgme_set_protocol (listctx, GPGME_PROTOCOL_CMS);

  k = key->kobj;
  gpgme_key_ref (k);
  while ((s = k->chain_id) && k->subkeys && strcmp (s, k->subkeys->fpr) )
    {
      putc ('\n', fp);
      err = gpgme_op_keylist_start (listctx, s, 0);
      gpgme_key_unref (k);
      k = NULL;
      if (!err)
	err = gpgme_op_keylist_next (listctx, &k);
      if (err)
        {
          fprintf (fp, _("Error finding issuer key: %s\n"),
                   gpgme_strerror (err));
          goto leave;
        }
      gpgme_op_keylist_end (listctx);
      
      print_key_info (k, fp);
      if (!--maxdepth)
        {
          putc ('\n', fp);
          fputs (_("Error: certification chain to long - stopping here\n"),
                 fp);
          break;
        }
    }

 leave:
  gpgme_key_unref (k);
  gpgme_release (listctx);
  safe_fclose (&fp);
  mutt_clear_error ();
  snprintf (cmd, sizeof (cmd), _("Key ID: 0x%s"),  crypt_keyid (key));
  mutt_do_pager (cmd, tempfile, 0, NULL);
}