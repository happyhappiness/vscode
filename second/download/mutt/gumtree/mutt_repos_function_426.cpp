static
pid_t smime_invoke_verify (FILE **smimein, FILE **smimeout, FILE **smimeerr,
			   int smimeinfd, int smimeoutfd, int smimeerrfd, 
			   const char *fname, const char *sig_fname, int opaque)
{
  return smime_invoke (smimein, smimeout, smimeerr, smimeinfd, smimeoutfd,
		       smimeerrfd, fname, sig_fname, NULL, NULL, NULL, NULL, NULL,
		       (opaque ? SmimeVerifyOpaqueCommand : SmimeVerifyCommand));
}