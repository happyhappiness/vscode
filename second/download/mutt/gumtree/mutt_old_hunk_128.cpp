  k = key->kobj;
  gpgme_key_ref (k);
  while ((s = k->chain_id) && k->subkeys && strcmp (s, k->subkeys->fpr) )
    {
      putc ('\n', fp);
      err = gpgme_op_keylist_start (listctx, s, 0);
      gpgme_key_release (k);
      k = NULL;
      if (!err)
	err = gpgme_op_keylist_next (listctx, &k);
      if (err)
        {
          fprintf (fp, _("Error finding issuer key: %s\n"),
