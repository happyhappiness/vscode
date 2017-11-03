static int pgp_gpgme_extract_keys (gpgme_data_t keydata, FILE** fp, int dryrun)
{
  /* there's no side-effect free way to view key data in GPGME,
   * so we import the key into a temporary keyring */
  char tmpdir[_POSIX_PATH_MAX];
  char tmpfile[_POSIX_PATH_MAX];
  gpgme_ctx_t tmpctx;
  gpgme_error_t err;
  gpgme_engine_info_t engineinfo;
  gpgme_key_t key;
  gpgme_user_id_t uid;
  gpgme_subkey_t subkey;
  const char* shortid;
  int len;
  char date[STRING];
  int more;
  int rc = -1;
  time_t tt;

  if ((err = gpgme_new (&tmpctx)) != GPG_ERR_NO_ERROR)
  {
    dprint (1, (debugfile, "Error creating GPGME context\n"));
    return rc;
  }
  
  if (dryrun)
  {
    snprintf (tmpdir, sizeof(tmpdir), "%s/mutt-gpgme-XXXXXX", Tempdir);
    if (!mkdtemp (tmpdir))
    {
      dprint (1, (debugfile, "Error creating temporary GPGME home\n"));
      goto err_ctx;
    }

    engineinfo = gpgme_ctx_get_engine_info (tmpctx);
    while (engineinfo && engineinfo->protocol != GPGME_PROTOCOL_OpenPGP)
      engineinfo = engineinfo->next;
    if (!engineinfo)
    {
      dprint (1, (debugfile, "Error finding GPGME PGP engine\n"));
      goto err_tmpdir;
    }

    err = gpgme_ctx_set_engine_info (tmpctx, GPGME_PROTOCOL_OpenPGP,
                                     engineinfo->file_name, tmpdir);
    if (err != GPG_ERR_NO_ERROR)
    {
      dprint (1, (debugfile, "Error setting GPGME context home\n"));
      goto err_tmpdir;
    }
  }

  if ((err = gpgme_op_import (tmpctx, keydata)) != GPG_ERR_NO_ERROR)
  {
    dprint (1, (debugfile, "Error importing key\n"));
    goto err_tmpdir;
  }

  mutt_mktemp (tmpfile, sizeof (tmpfile));
  *fp = safe_fopen (tmpfile, "w+");
  if (!*fp)
  {
    mutt_perror (tmpfile);
    goto err_tmpdir;
  }
  unlink (tmpfile);

  err = gpgme_op_keylist_start (tmpctx, NULL, 0);
  while (!err)
  {
    if ((err = gpgme_op_keylist_next (tmpctx, &key)))
      break;
    uid = key->uids;
    subkey = key->subkeys;
    more = 0;
    while (subkey)
    {
      shortid = subkey->keyid;
      len = mutt_strlen (subkey->keyid);
      if (len > 8)
        shortid += len - 8;
      tt = subkey->timestamp;
      strftime (date, sizeof (date), "%Y-%m-%d", localtime (&tt));

      if (!more)
        fprintf (*fp, "%s %5.5s %d/%8s %s %s\n", more ? "sub" : "pub",
                 gpgme_pubkey_algo_name (subkey->pubkey_algo), subkey->length,
                 shortid, date, uid->uid);
      else
        fprintf (*fp, "%s %5.5s %d/%8s %s\n", more ? "sub" : "pub",
                 gpgme_pubkey_algo_name (subkey->pubkey_algo), subkey->length,
                 shortid, date);      
      subkey = subkey->next;
      more = 1;
    }
    gpgme_key_unref (key);
  }
  if (gpg_err_code (err) != GPG_ERR_EOF)
  {
    dprint (1, (debugfile, "Error listing keys\n"));
    goto err_fp;
  }

  rc = 0;

err_fp:
  if (rc)
    safe_fclose (fp);
err_tmpdir:
  if (dryrun)
    mutt_rmtree (tmpdir);
err_ctx:
  gpgme_release (tmpctx);

  return rc;
}