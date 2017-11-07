static int fetch_one(struct remote *remote, int argc, const char **argv)
{
	static const char **refs = NULL;
	struct refspec *refspec;
	int ref_nr = 0;
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
			prune = fetch_prune_config;
		else
			prune = PRUNE_BY_DEFAULT;
	}

	if (argc > 0) {
		int j = 0;
		int i;
		refs = xcalloc(argc + 1, sizeof(const char *));
		for (i = 0; i < argc; i++) {
			if (!strcmp(argv[i], "tag")) {
				char *ref;
				i++;
				if (i >= argc)
					die(_("You need to specify a tag name."));
				ref = xmalloc(strlen(argv[i]) * 2 + 22);
				strcpy(ref, "refs/tags/");
				strcat(ref, argv[i]);
				strcat(ref, ":refs/tags/");
				strcat(ref, argv[i]);
				refs[j++] = ref;
			} else
				refs[j++] = argv[i];
		}
		refs[j] = NULL;
		ref_nr = j;
	}

	sigchain_push_common(unlock_pack_on_signal);
	atexit(unlock_pack);
	refspec = parse_fetch_refspec(ref_nr, refs);
	exit_code = do_fetch(gtransport, refspec, ref_nr);
	free_refspec(ref_nr, refspec);
	transport_disconnect(gtransport);
	gtransport = NULL;
	return exit_code;
}