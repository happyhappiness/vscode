pid_t pgp_invoke_list_keys (FILE **pgpin, FILE **pgpout, FILE **pgperr,
			    int pgpinfd, int pgpoutfd, int pgperrfd, 
			    pgp_ring_t keyring, LIST *hints)
{
  char uids[HUGE_STRING];
  char tmpuids[HUGE_STRING];
  char quoted[HUGE_STRING];
  
  *uids = '\0';
  
  for (; hints; hints = hints->next)
  {
    mutt_quote_filename (quoted, sizeof (quoted), (char *) hints->data);
    snprintf (tmpuids, sizeof (tmpuids), "%s %s", uids, quoted);
    strcpy (uids, tmpuids);	/* __STRCPY_CHECKED__ */
  }

  return pgp_invoke (pgpin, pgpout, pgperr, pgpinfd, pgpoutfd, pgperrfd,
		     0, NULL, NULL, PgpSignAs, uids,
		     keyring == PGP_SECRING ? PgpListSecringCommand :
		     PgpListPubringCommand);
}