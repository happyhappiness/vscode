
		/*
		 * Try to give more helpful suggestion.
		 * new_branch && argc > 1 will be caught later.
		 */
		if (opts.new_branch && argc == 1)
			die(_("'%s' is not a commit and a branch '%s' cannot be created from it"),
				argv[0], opts.new_branch);

		if (opts.force_detach)
			die(_("git checkout: --detach does not take a path argument '%s'"),
			    argv[0]);

		if (1 < !!opts.writeout_stage + !!opts.force + !!opts.merge)
