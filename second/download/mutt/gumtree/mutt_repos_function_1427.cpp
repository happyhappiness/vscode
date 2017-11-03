pid_t pgp_invoke_verify_key (FILE **pgpin, FILE **pgpout, FILE **pgperr,
			     int pgpinfd, int pgpoutfd, int pgperrfd, 
			     const char *uids)
{
  return pgp_invoke (pgpin, pgpout, pgperr, pgpinfd, pgpoutfd, pgperrfd,
		     0, NULL, NULL, PgpSignAs, uids,
		     PgpVerifyKeyCommand);
}