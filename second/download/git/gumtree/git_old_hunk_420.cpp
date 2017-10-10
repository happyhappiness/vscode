			/*
			 * Asking for --more in reflog mode does not
			 * make sense.  --list is Ok.
			 *
			 * Also --all and --remotes do not make sense either.
			 */
			die("--reflog is incompatible with --all, --remotes, "
			    "--independent or --merge-base");
	}

	/* If nothing is specified, show all branches by default */
	if (ac <= topics && all_heads + all_remotes == 0)
		all_heads = 1;

