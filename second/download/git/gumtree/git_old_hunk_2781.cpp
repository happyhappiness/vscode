	int i;
	int ret = 0;
	int remote_branch = 0;
	struct strbuf bname = STRBUF_INIT;

	switch (kinds) {
	case REF_REMOTE_BRANCH:
		fmt = "refs/remotes/%s";
		/* For subsequent UI messages */
		remote_branch = 1;

		force = 1;
		break;
	case REF_LOCAL_BRANCH:
		fmt = "refs/heads/%s";
		break;
	default:
		die(_("cannot use -a with -d"));
	}

