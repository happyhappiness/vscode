static int set_signer (gpgme_ctx_t ctx, int for_smime)
{
  char *signid = for_smime ? SmimeDefaultKey: PgpSignAs;
  gpgme_error_t err;
  gpgme_ctx_t listctx;
  gpgme_key_t key, key2;

  if (!signid || !*signid)
    return 0;

  listctx = create_gpgme_context (for_smime);
  err = gpgme_op_keylist_start (listctx, signid, 1);
  if (!err)
    err = gpgme_op_keylist_next (listctx, &key);
  if (err)
    {
      gpgme_release (listctx);
      mutt_error (_("secret key `%s' not found: %s\n"),
                  signid, gpgme_strerror (err));
      return -1;
    }
  err = gpgme_op_keylist_next (listctx, &key2);
  if (!err)
    {
      gpgme_key_unref (key);
      gpgme_key_unref (key2);
      gpgme_release (listctx);
      mutt_error (_("ambiguous specification of secret key `%s'\n"),
                  signid);
      return -1;
    }
  gpgme_op_keylist_end (listctx);
  gpgme_release (listctx);

  gpgme_signers_clear (ctx);
  err = gpgme_signers_add (ctx, key);
  gpgme_key_unref (key);
  if (err)
    {
      mutt_error (_("error setting secret key `%s': %s\n"),
                  signid, gpgme_strerror (err));
      return -1;
    }
  return 0;
}