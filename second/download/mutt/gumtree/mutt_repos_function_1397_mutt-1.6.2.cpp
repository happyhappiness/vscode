pid_t pgp_invoke_verify (FILE **pgpin, FILE **pgpout, FILE **pgperr,
			 int pgpinfd, int pgpoutfd, int pgperrfd, 
			 const char *fname, const char *sig_fname)
{
  return pgp_invoke (pgpin, pgpout, pgperr, pgpinfd, pgpoutfd, pgperrfd,
		     0, fname, sig_fname, PgpSignAs, NULL, PgpVerifyCommand);
}