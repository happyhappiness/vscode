static
pid_t smime_invoke_decrypt (FILE **smimein, FILE **smimeout, FILE **smimeerr,
			    int smimeinfd, int smimeoutfd, int smimeerrfd, 
			    const char *fname)
{
  return smime_invoke (smimein, smimeout, smimeerr, smimeinfd, smimeoutfd,
		       smimeerrfd, fname, NULL, NULL, NULL, SmimeKeyToUse,
		       SmimeCertToUse, NULL, SmimeDecryptCommand);
}