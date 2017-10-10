		if (!strcmp(argv[0], "HEAD"))
			die(_("it does not make sense to create 'HEAD' manually"));

		if (!branch)
			die(_("no such branch '%s'"), argv[0]);

		if (kinds != REF_LOCAL_BRANCH)
			die(_("-a and -r options to 'git branch' do not make sense with a branch name"));

		if (track == BRANCH_TRACK_OVERRIDE)
			fprintf(stderr, _("The --set-upstream flag is deprecated and will be removed. Consider using --track or --set-upstream-to\n"));

		strbuf_addf(&buf, "refs/remotes/%s", branch->name);
