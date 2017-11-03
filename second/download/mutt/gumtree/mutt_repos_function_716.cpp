static BODY *decrypt_part (BODY *a, STATE *s, FILE *fpout, int is_smime,
                           int *r_is_signed)
{
  struct stat info;
  BODY *tattach;
  int err = 0;
  gpgme_ctx_t ctx;
  gpgme_data_t ciphertext, plaintext;
  int maybe_signed = 0;
  int anywarn = 0;
  int sig_stat = 0;

  if (r_is_signed)
    *r_is_signed = 0;

  ctx = create_gpgme_context (is_smime);

 restart:
  /* Make a data object from the body, create context etc. */
  ciphertext = file_to_data_object (s->fpin, a->offset, a->length);
  if (!ciphertext)
    return NULL;
  plaintext = create_gpgme_data ();

  /* Do the decryption or the verification in case of the S/MIME hack. */
  if ((! is_smime) || maybe_signed)
    {
      if (! is_smime)
	err = gpgme_op_decrypt_verify (ctx, ciphertext, plaintext);
      else if (maybe_signed)
	err = gpgme_op_verify (ctx, ciphertext, NULL, plaintext);

      if (err == GPG_ERR_NO_ERROR)
      {
	/* Check whether signatures have been verified.  */
	gpgme_verify_result_t verify_result = gpgme_op_verify_result (ctx);
	if (verify_result->signatures)
	  sig_stat = 1;
      }
    }
  else
    err = gpgme_op_decrypt (ctx, ciphertext, plaintext);
  gpgme_data_release (ciphertext);
  if (err)
    {
      if (is_smime && !maybe_signed
          && gpg_err_code (err) == GPG_ERR_NO_DATA)
        {
	  /* Check whether this might be a signed message despite what
             the mime header told us.  Retry then.  gpgsm returns the
             error information "unsupported Algorithm '?'" but gpgme
             will not store this unknown algorithm, thus we test that
             it has not been set. */
	  gpgme_decrypt_result_t result;

	  result = gpgme_op_decrypt_result (ctx);
	  if (!result->unsupported_algorithm)
            {
              maybe_signed = 1;
              gpgme_data_release (plaintext);
              goto restart;
            }
        }
      mutt_need_hard_redraw ();
      if ((s->flags & MUTT_DISPLAY))
        {
          char buf[200];
          
          snprintf (buf, sizeof(buf)-1, 
                    _("[-- Error: decryption failed: %s --]\n\n"),
                    gpgme_strerror (err));
          state_attach_puts (buf, s);
        }
      gpgme_data_release (plaintext);
      gpgme_release (ctx);
      return NULL;
  }
  mutt_need_hard_redraw ();

  /* Read the output from GPGME, and make sure to change CRLF to LF,
     otherwise read_mime_header has a hard time parsing the message.  */
  if (data_object_to_stream (plaintext, fpout))
    {
      gpgme_data_release (plaintext);
      gpgme_release (ctx);
      return NULL;
    }
  gpgme_data_release (plaintext);

  a->is_signed_data = 0;
  if (sig_stat)
    {
      int res, idx;
      int anybad = 0;
      
      if (maybe_signed)
        a->is_signed_data = 1;
      if(r_is_signed)
        *r_is_signed = -1; /* A signature exists. */

      if ((s->flags & MUTT_DISPLAY))
        state_attach_puts (_("[-- Begin signature "
                             "information --]\n"), s);
      for(idx = 0; (res = show_one_sig_status (ctx, idx, s)) != -1; idx++)
        {
          if (res == 1)
            anybad = 1;
          else if (res == 2)
            anywarn = 1;
        }
      if (!anybad && idx && r_is_signed && *r_is_signed)
        *r_is_signed = anywarn? 2:1; /* Good signature. */
      
      if ((s->flags & MUTT_DISPLAY))
        state_attach_puts (_("[-- End signature "
                             "information --]\n\n"), s);
    }
  gpgme_release (ctx); ctx = NULL;

  fflush (fpout);
  rewind (fpout);
  tattach = mutt_read_mime_header (fpout, 0);
  if (tattach)
    {
      /*
       * Need to set the length of this body part.
       */
      fstat (fileno (fpout), &info);
      tattach->length = info.st_size - tattach->offset;
      
      tattach->warnsig = anywarn;

      /* See if we need to recurse on this MIME part.  */
      mutt_parse_part (fpout, tattach);
    }

  return tattach;
}