  snprintf (SmimeKeyToUse, sizeof (SmimeKeyToUse), "%s/%s", 
	   NONULL(SmimeKeys), SmimeDefaultKey);

  snprintf (SmimeCertToUse, sizeof (SmimeCertToUse), "%s/%s",
	   NONULL(SmimeCertificates), SmimeDefaultKey);
  
  default_key = smime_get_key_by_hash (SmimeDefaultKey, 1);
  if ((! default_key) ||
      (! mutt_strcmp ("?", default_key->issuer)))
    intermediates = SmimeDefaultKey; /* so openssl won't complain in any case */
  else
    intermediates = default_key->issuer;

  snprintf (SmimeIntermediateToUse, sizeof (SmimeIntermediateToUse), "%s/%s",
	   NONULL(SmimeCertificates), intermediates);

  smime_free_key (&default_key);
  


  if ((thepid = smime_invoke_sign (&smimein, NULL, &smimeerr,
				 -1, fileno (smimeout), -1, filetosign)) == -1)
  {
    mutt_perror _("Can't open OpenSSL subprocess!");
    safe_fclose (&smimeout);
    mutt_unlink (signedfile);
    mutt_unlink (filetosign);
    return NULL;
  }
  fputs (SmimePass, smimein);
  fputc ('\n', smimein);
  safe_fclose (&smimein);
  
