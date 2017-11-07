pid_t pgp_invoke_decode (FILE **pgpin, FILE **pgpout, FILE **pgperr,
			 int pgpinfd, int pgpoutfd, int pgperrfd, 
			 const char *fname, short need_passphrase)
{
  return pgp_invoke (pgpin, pgpout, pgperr, pgpinfd, pgpoutfd, pgperrfd,
		     need_passphrase, fname, NULL, PgpSignAs, NULL, 
		     PgpDecodeCommand);
}