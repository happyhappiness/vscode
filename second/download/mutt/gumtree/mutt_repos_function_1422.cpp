pid_t pgp_invoke_encrypt (FILE **pgpin, FILE **pgpout, FILE **pgperr,
			  int pgpinfd, int pgpoutfd, int pgperrfd,
			  const char *fname, const char *uids, int sign)
{
  if (sign)
    return pgp_invoke (pgpin, pgpout, pgperr, pgpinfd, pgpoutfd, pgperrfd,
		       1, fname, NULL, PgpSignAs, uids, 
		       PgpEncryptSignCommand);
  else
    return pgp_invoke (pgpin, pgpout, pgperr, pgpinfd, pgpoutfd, pgperrfd,
		       0, fname, NULL, PgpSignAs, uids,
		       PgpEncryptOnlyCommand);
}