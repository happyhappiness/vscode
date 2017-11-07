pid_t pgp_invoke_traditional (FILE **pgpin, FILE **pgpout, FILE **pgperr,
			      int pgpinfd, int pgpoutfd, int pgperrfd,
			      const char *fname, const char *uids, int flags)
{
  if (flags & PGPENCRYPT)
    return pgp_invoke (pgpin, pgpout, pgperr, pgpinfd, pgpoutfd, pgperrfd,
		       flags & PGPSIGN ? 1 : 0, fname, NULL, PgpSignAs, uids, 
		       flags & PGPSIGN ? PgpEncryptSignCommand : PgpEncryptOnlyCommand);
  else
    return pgp_invoke (pgpin, pgpout, pgperr, pgpinfd, pgpoutfd, pgperrfd,
		       1, fname, NULL, PgpSignAs, NULL,
		       PgpClearSignCommand);
}