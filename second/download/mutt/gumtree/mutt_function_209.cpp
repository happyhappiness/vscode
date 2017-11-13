static int verify_one (BODY *sigbdy, STATE *s,
                       const char *tempfile, int is_smime)
{
  int badsig = -1;
  int anywarn = 0;
  int err;
  gpgme_ctx_t ctx;
  gpgme_data_t signature, message;

  signature = file_to_data_object (s->fpin, sigbdy->offset, sigbdy->length);
  if (!signature)
    return -1;

  /* We need to tell gpgme about the encoding because the backend can't
     auto-detect plain base-64 encoding which is used by S/MIME. */
  if (is_smime)
    gpgme_data_set_encoding (signature, GPGME_DATA_ENCODING_BASE64);

  err = gpgme_data_new_from_file (&message, tempfile, 1);
  if (err) 
    {
      gpgme_data_release (signature);
      mutt_error (_("error allocating data object: %s\n"), gpgme_strerror (err));
      return -1;
    }
  ctx = create_gpgme_context (is_smime);

  /* Note: We don't need a current time output because GPGME avoids
     such an attack by separating the meta information from the
     data. */
  state_attach_puts (_("[-- Begin signature information --]\n"), s);

  err = gpgme_op_verify (ctx, signature, message, NULL);
  gpgme_data_release (message);
  gpgme_data_release (signature);

  mutt_need_hard_redraw ();
  if (err)
    {
      char buf[200];
      
      snprintf (buf, sizeof(buf)-1, 
                _("Error: verification failed: %s\n"),
                gpgme_strerror (err));
      state_attach_puts (buf, s);
    }
  else
    { /* Verification succeeded, see what the result is. */
      int res, idx;
      int anybad = 0;

      if (signature_key)
	{
	  gpgme_key_unref (signature_key);
	  signature_key = NULL;
	}

      for(idx=0; (res = show_one_sig_status (ctx, idx, s)) != -1; idx++)
        {
          if (res == 1)
            anybad = 1;
          else if (res == 2)
            anywarn = 2;
        }
      if (!anybad)
        badsig = 0;
    }

  if (!badsig)
    {
      gpgme_verify_result_t result;
      gpgme_sig_notation_t notation;
      gpgme_signature_t signature;
      int non_pka_notations;

      result = gpgme_op_verify_result (ctx);
      if (result)
      {
	for (signature = result->signatures; signature;
             signature = signature->next)
	{
	  non_pka_notations = 0;
	  for (notation = signature->notations; notation;
	       notation = notation->next)
	    if (! is_pka_notation (notation))
	      non_pka_notations++;

	  if (non_pka_notations)
	  {
	    char buf[SHORT_STRING];
	    snprintf (buf, sizeof (buf),
		      _("*** Begin Notation (signature by: %s) ***\n"),
		      signature->fpr);
	    state_attach_puts (buf, s);
	    for (notation = signature->notations; notation;
                 notation = notation->next)
	    {
	      if (is_pka_notation (notation))
		continue;

	      if (notation->name)
	      {
		state_attach_puts (notation->name, s);
		state_attach_puts ("=", s);
	      }
	      if (notation->value)
	      {
		state_attach_puts (notation->value, s);
		if (!(*notation->value
                      && (notation->value[strlen (notation->value)-1]=='\n')))
		  state_attach_puts ("\n", s);
	      }
	    }
	    state_attach_puts (_("*** End Notation ***\n"), s);
	  }
	}
      }
    }

  gpgme_release (ctx);
  
  state_attach_puts (_("[-- End signature information --]\n\n"), s);
  dprint (1, (debugfile, "verify_one: returning %d.\n", badsig));
  
  return badsig? 1: anywarn? 2 : 0;
}