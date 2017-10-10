	int exit_code;

	if (!remote)
		die(_("No remote repository specified.  Please, specify either a URL or a\n"
		    "remote name from which new revisions should be fetched."));

	gtransport = prepare_transport(remote);

	if (prune < 0) {
		/* no command line request */
		if (0 <= gtransport->remote->prune)
			prune = gtransport->remote->prune;
		else if (0 <= fetch_prune_config)
