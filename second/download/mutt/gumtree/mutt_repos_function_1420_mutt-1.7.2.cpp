pid_t pgp_invoke_decrypt (FILE **pgpin, FILE **pgpout, FILE **pgperr,
			  int pgpinfd, int pgpoutfd, int pgperrfd, 
			  const char *fname)
{
  return pgp_invoke (pgpin, pgpout, pgperr, pgpinfd, pgpoutfd, pgperrfd,
		     1, fname, NULL, PgpSignAs, NULL, PgpDecryptCommand);
}