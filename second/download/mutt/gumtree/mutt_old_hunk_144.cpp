  snprintf (SmimeKeyToUse, sizeof (SmimeKeyToUse), "%s/%s", 
	   NONULL(SmimeKeys), SmimeDefaultKey);

  snprintf (SmimeCertToUse, sizeof (SmimeCertToUse), "%s/%s",
	   NONULL(SmimeCertificates), SmimeDefaultKey);
  
  snprintf (SmimeIntermediateToUse, sizeof (SmimeIntermediateToUse), "%s/%s",
	   NONULL(SmimeCertificates), intermediates);
  


  if ((thepid = smime_invoke_sign (&smimein, NULL, &smimeerr,
				 -1, fileno (smimeout), -1, filetosign)) == -1)
  {
    mutt_perror _("Can't open OpenSSL subprocess!");
    safe_fclose (&smimeout);
    mutt_unlink (signedfile);
    mutt_unlink (filetosign);
    if (intermediates != SmimeDefaultKey)
      FREE (&intermediates);
    return NULL;
  }
  fputs (SmimePass, smimein);
  fputc ('\n', smimein);
  safe_fclose (&smimein);
  
