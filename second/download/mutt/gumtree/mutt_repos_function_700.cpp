static char *encrypt_gpgme_object (gpgme_data_t plaintext, gpgme_key_t *rset,
                                   int use_smime, int combined_signed)
{
  gpgme_error_t err;
  gpgme_ctx_t ctx;
  gpgme_data_t ciphertext;
  char *outfile;

  ctx = create_gpgme_context (use_smime);
  if (!use_smime) 
      gpgme_set_armor (ctx, 1);

  ciphertext = create_gpgme_data ();

  if (combined_signed)
    {
      if (set_signer (ctx, use_smime))
        {
          gpgme_data_release (ciphertext);
          gpgme_release (ctx);
          return NULL;
        }

      if (option (OPTCRYPTUSEPKA))
	{
	  err = set_pka_sig_notation (ctx);
	  if (err)
	    {
	      gpgme_data_release (ciphertext);
	      gpgme_release (ctx);
	      return NULL;
	    }
	}

      err = gpgme_op_encrypt_sign (ctx, rset, GPGME_ENCRYPT_ALWAYS_TRUST,
                                   plaintext, ciphertext);
    }
  else
    err = gpgme_op_encrypt (ctx, rset, GPGME_ENCRYPT_ALWAYS_TRUST,
                            plaintext, ciphertext);
  mutt_need_hard_redraw ();
  if (err)
    {
      mutt_error (_("error encrypting data: %s\n"), gpgme_strerror (err));
      gpgme_data_release (ciphertext);
      gpgme_release (ctx);
      return NULL;
    }

  gpgme_release (ctx);

  outfile = data_object_to_tempfile (ciphertext, NULL, NULL);
  gpgme_data_release (ciphertext);
  return outfile;
}