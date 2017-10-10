	char *name = NULL;
	const char *fmt;
	int i;
	int ret = 0;
	int remote_branch = 0;
	struct strbuf bname = STRBUF_INIT;

	switch (kinds) {
	case FILTER_REFS_REMOTES:
		fmt = "refs/remotes/%s";
		/* For subsequent UI messages */
		remote_branch = 1;

		force = 1;
		break;
	case FILTER_REFS_BRANCHES:
		fmt = "refs/heads/%s";
		break;
	default:
		die(_("cannot use -a with -d"));
	}

	if (!force) {
