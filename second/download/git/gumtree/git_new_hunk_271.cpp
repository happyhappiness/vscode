		parse_commit_or_die(new->commit);
		*source_tree = new->commit->tree;
	}

	if (!*source_tree)                   /* case (1): want a tree */
		die(_("reference is not a tree: %s"), arg);
	if (!has_dash_dash) {	/* case (3).(d) -> (1) */
		/*
		 * Do not complain the most common case
		 *	git checkout branch
		 * even if there happen to be a file called 'branch';
		 * it would be extremely annoying.
		 */
		if (argc)
			verify_non_filename(opts->prefix, arg);
	} else {
		argcount++;
		argv++;
		argc--;
	}

