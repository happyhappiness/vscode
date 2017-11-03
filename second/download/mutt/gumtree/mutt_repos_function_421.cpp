static
pid_t smime_invoke_encrypt (FILE **smimein, FILE **smimeout, FILE **smimeerr,
			    int smimeinfd, int smimeoutfd, int smimeerrfd,
			    const char *fname, const char *uids)
{
  return smime_invoke (smimein, smimeout, smimeerr,
		       smimeinfd, smimeoutfd, smimeerrfd,
		       fname, NULL, SmimeCryptAlg, NULL, NULL, uids, NULL,
		       SmimeEncryptCommand);
}