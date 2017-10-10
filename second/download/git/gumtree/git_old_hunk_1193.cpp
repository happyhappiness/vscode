	if (autocorrect && n == 1 && SIMILAR_ENOUGH(best_similarity)) {
		const char *assumed = main_cmds.names[0]->name;
		main_cmds.names[0] = NULL;
		clean_cmdnames(&main_cmds);
		fprintf_ln(stderr,
			   _("WARNING: You called a Git command named '%s', "
			     "which does not exist.\n"
			     "Continuing under the assumption that you meant '%s'"),
			cmd, assumed);
		if (autocorrect > 0) {
			fprintf_ln(stderr, _("in %0.1f seconds automatically..."),
				(float)autocorrect/10.0);
			sleep_millisec(autocorrect * 100);
		}
		return assumed;
	}

	fprintf_ln(stderr, _("git: '%s' is not a git command. See 'git --help'."), cmd);
