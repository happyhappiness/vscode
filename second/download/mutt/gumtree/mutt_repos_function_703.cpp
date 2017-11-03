static BODY *sign_message (BODY *a, int use_smime)
{
  BODY *t;
  char *sigfile;
  int err = 0;
  char buf[100];
  gpgme_ctx_t ctx;
  gpgme_data_t message, signature;
  gpgme_sign_result_t sigres;

  convert_to_7bit (a); /* Signed data _must_ be in 7-bit format. */

  message = body_to_data_object (a, 1);
  if (!message)
     return NULL;
  signature = create_gpgme_data ();

  ctx = create_gpgme_context (use_smime);
  if (!use_smime)
    gpgme_set_armor (ctx, 1);

  if (set_signer (ctx, use_smime))
    {
      gpgme_data_release (signature);
      gpgme_data_release (message);
      gpgme_release (ctx);
      return NULL;
    }

  if (option (OPTCRYPTUSEPKA))
    {
      err = set_pka_sig_notation (ctx);
      if (err)
	{
	  gpgme_data_release (signature);
	  gpgme_data_release (message);
	  gpgme_release (ctx);
	  return NULL;
	}
    }

  err = gpgme_op_sign (ctx, message, signature, GPGME_SIG_MODE_DETACH );
  mutt_need_hard_redraw ();
  gpgme_data_release (message);
  if (err)
    {
      gpgme_data_release (signature);
      gpgme_release (ctx);
      mutt_error (_("error signing data: %s\n"), gpgme_strerror (err));
      return NULL;
    }
  /* Check for zero signatures generated.  This can occur when $pgp_sign_as is
   * unset and there is no default key specified in ~/.gnupg/gpg.conf
   */
  sigres = gpgme_op_sign_result (ctx);
  if (!sigres->signatures)
  {
      gpgme_data_release (signature);
      gpgme_release (ctx);
      mutt_error (_("$pgp_sign_as unset and no default key specified in ~/.gnupg/gpg.conf"));
      return NULL;
  }

  sigfile = data_object_to_tempfile (signature, NULL, NULL);
  gpgme_data_release (signature);
  if (!sigfile)
    {
      gpgme_release (ctx);
      return NULL;
    }

  t = mutt_new_body ();
  t->type = TYPEMULTIPART;
  t->subtype = safe_strdup ("signed");
  t->encoding = ENC7BIT;
  t->use_disp = 0;
  t->disposition = DISPINLINE;

  mutt_generate_boundary (&t->parameter);
  mutt_set_parameter ("protocol",
                      use_smime? "application/pkcs7-signature"
                               : "application/pgp-signature",
                      &t->parameter);
  /* Get the micalg from gpgme.  Old gpgme versions don't support this
     for S/MIME so we assume sha-1 in this case. */
  if (!get_micalg (ctx, use_smime, buf, sizeof buf))
    mutt_set_parameter ("micalg", buf, &t->parameter);
  else if (use_smime)
    mutt_set_parameter ("micalg", "sha1", &t->parameter);
  gpgme_release (ctx);

  t->parts = a;
  a = t;

  t->parts->next = mutt_new_body ();
  t = t->parts->next;
  t->type = TYPEAPPLICATION;
  if (use_smime)
    {
      t->subtype = safe_strdup ("pkcs7-signature");
      mutt_set_parameter ("name", "smime.p7s", &t->parameter);
      t->encoding = ENCBASE64; 
      t->use_disp = 1;
      t->disposition = DISPATTACH;
      t->d_filename = safe_strdup ("smime.p7s");
    }
  else
    {
      t->subtype = safe_strdup ("pgp-signature");
      mutt_set_parameter ("name", "signature.asc", &t->parameter);
      t->use_disp = 0;
      t->disposition = DISPNONE;
      t->encoding = ENC7BIT;
    }
  t->filename = sigfile;
  t->unlink = 1; /* ok to remove this file after sending. */

  return a;
}