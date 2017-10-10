		if (opt_rebase)
			fprintf_ln(stderr, _("Please specify which branch you want to rebase against."));
		else
			fprintf_ln(stderr, _("Please specify which branch you want to merge with."));
		fprintf_ln(stderr, _("See git-pull(1) for details."));
		fprintf(stderr, "\n");
		fprintf_ln(stderr, "    git pull <remote> <branch>");
		fprintf(stderr, "\n");
	} else if (!curr_branch->merge_nr) {
		const char *remote_name = NULL;

		if (for_each_remote(get_only_remote, &remote_name) || !remote_name)
			remote_name = "<remote>";

		fprintf_ln(stderr, _("There is no tracking information for the current branch."));
		if (opt_rebase)
			fprintf_ln(stderr, _("Please specify which branch you want to rebase against."));
		else
			fprintf_ln(stderr, _("Please specify which branch you want to merge with."));
		fprintf_ln(stderr, _("See git-pull(1) for details."));
		fprintf(stderr, "\n");
		fprintf_ln(stderr, "    git pull <remote> <branch>");
		fprintf(stderr, "\n");
		fprintf_ln(stderr, _("If you wish to set tracking information for this branch you can do so with:\n"
				"\n"
				"    git branch --set-upstream-to=%s/<branch> %s\n"),
				remote_name, curr_branch->name);
	} else
		fprintf_ln(stderr, _("Your configuration specifies to merge with the ref '%s'\n"
			"from the remote, but no such ref was fetched."),
			*curr_branch->merge_name);
	exit(1);
}
