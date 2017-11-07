static int browse_verify_namespace (IMAP_DATA* idata,
  IMAP_NAMESPACE_INFO *nsi, int nns)
{
  char buf[LONG_STRING];
  int i = 0;
  char *name;
  char delim;

  for (i = 0; i < nns; i++, nsi++)
  {
    /* Cyrus gives back nothing if the % isn't added. This may return lots
     * of data in some cases, I guess, but I currently feel that's better
     * than invisible namespaces */
    if (nsi->delim)
      snprintf (buf, sizeof (buf), "%s \"\" \"%s%c%%\"",
		option (OPTIMAPLSUB) ? "LSUB" : "LIST", nsi->prefix,
		nsi->delim);
    else
      snprintf (buf, sizeof (buf), "%s \"\" \"%s%%\"",
		option (OPTIMAPLSUB) ? "LSUB" : "LIST", nsi->prefix);

    imap_cmd_start (idata, buf);

    nsi->listable = 0;
    nsi->home_namespace = 0;
    do 
    {
      if (imap_parse_list_response(idata, &name, &nsi->noselect,
          &nsi->noinferiors, &delim) != 0)
	return -1;
      nsi->listable |= (name != NULL);
    }
    while ((ascii_strncmp (idata->cmd.buf, idata->cmd.seq, SEQLEN) != 0));
  }

  return 0;
}