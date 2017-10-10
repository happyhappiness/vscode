			die(_("branch '%s' does not exist"), branch->name);

		/*
		 * create_branch takes care of setting up the tracking
		 * info and making sure new_upstream is correct
		 */
		create_branch(head, branch->name, new_upstream, 0, 0, 0, quiet, BRANCH_TRACK_OVERRIDE);
	} else if (unset_upstream) {
		struct branch *branch = branch_get(argv[0]);
		struct strbuf buf = STRBUF_INIT;

		if (argc > 1)
			die(_("too many branches to unset upstream"));
