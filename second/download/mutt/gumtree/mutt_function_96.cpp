static int show_one_sig_status (gpgme_ctx_t ctx, int idx, STATE *s)
{
  const char *fpr;
  gpgme_key_t key = NULL;
  int i, anybad = 0, anywarn = 0;
  unsigned int sum;
  gpgme_verify_result_t result;
  gpgme_signature_t sig;
  gpgme_error_t err = GPG_ERR_NO_ERROR;

  result = gpgme_op_verify_result (ctx);
  if (result)
    {
      /* FIXME: this code should use a static variable and remember
	 the current position in the list of signatures, IMHO.
	 -moritz.  */

      for (i = 0, sig = result->signatures; sig && (i < idx);
           i++, sig = sig->next)
        ;
      if (! sig)
	return -1;		/* Signature not found.  */

      if (signature_key)
	{
	  gpgme_key_release (signature_key);
	  signature_key = NULL;
	}
      
      fpr = sig->fpr;
      sum = sig->summary;

      if (gpg_err_code (sig->status) != GPG_ERR_NO_ERROR)
	anybad = 1;

      err = gpgme_get_key (ctx, fpr, &key, 0); /* secret key?  */
      if (! err)
	{
	  if (! signature_key)
	    signature_key = key;
	}
      else
       {
          key = NULL; /* Old gpgme versions did not set KEY to NULL on
                         error.   Do it here to avoid a double free. */
       }

      if (!s || !s->fpout || !(s->flags & M_DISPLAY))
	; /* No state information so no way to print anything. */
      else if (err)
	{
          state_attach_puts (_("Error getting key information: "), s);
          state_attach_puts ( gpgme_strerror (err), s );
          state_attach_puts ("\n", s);
          anybad = 1;
	}
      else if ((sum & GPGME_SIGSUM_GREEN))
      {
        print_smime_keyinfo (_("Good signature from:"), sig, key, s);
	if (show_sig_summary (sum, ctx, key, idx, s, sig))
	  anywarn = 1;
	show_one_sig_validity (ctx, idx, s);
      }
      else if ((sum & GPGME_SIGSUM_RED))
      {
        print_smime_keyinfo (_("*BAD* signature from:"), sig, key, s);
        show_sig_summary (sum, ctx, key, idx, s, sig);
      }
      else if (!anybad && key && (key->protocol == GPGME_PROTOCOL_OpenPGP))
      { /* We can't decide (yellow) but this is a PGP key with a good
           signature, so we display what a PGP user expects: The name,
	   fingerprint and the key validity (which is neither fully or
	   ultimate). */
        print_smime_keyinfo (_("Good signature from:"), sig, key, s);
	show_one_sig_validity (ctx, idx, s);
	show_fingerprint (key,s);
	if (show_sig_summary (sum, ctx, key, idx, s, sig))
	  anywarn = 1;
      }
      else /* can't decide (yellow) */
      {
        print_smime_keyinfo (_("Problem signature from:"), sig, key, s);
        state_attach_puts (_("               expires: "), s);
        print_time (sig->exp_timestamp, s);
        state_attach_puts ("\n", s);
	show_sig_summary (sum, ctx, key, idx, s, sig);
        anywarn = 1;
      }

      if (key != signature_key)
	gpgme_key_release (key);
    }

  return anybad ? 1 : anywarn ? 2 : 0;
}