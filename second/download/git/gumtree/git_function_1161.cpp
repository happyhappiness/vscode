const char *help_unknown_cmd(const char *cmd)
{
	int i, n, best_similarity = 0;
	struct cmdnames main_cmds, other_cmds;

	memset(&main_cmds, 0, sizeof(main_cmds));
	memset(&other_cmds, 0, sizeof(other_cmds));
	memset(&aliases, 0, sizeof(aliases));

	git_config(git_unknown_cmd_config, NULL);

	load_command_list("git-", &main_cmds, &other_cmds);

	add_cmd_list(&main_cmds, &aliases);
	add_cmd_list(&main_cmds, &other_cmds);
	QSORT(main_cmds.names, main_cmds.cnt, cmdname_compare);
	uniq(&main_cmds);

	/* This abuses cmdname->len for levenshtein distance */
	for (i = 0, n = 0; i < main_cmds.cnt; i++) {
		int cmp = 0; /* avoid compiler stupidity */
		const char *candidate = main_cmds.names[i]->name;

		/*
		 * An exact match means we have the command, but
		 * for some reason exec'ing it gave us ENOENT; probably
		 * it's a bad interpreter in the #! line.
		 */
		if (!strcmp(candidate, cmd))
			die(_(bad_interpreter_advice), cmd, cmd);

		/* Does the candidate appear in common_cmds list? */
		while (n < ARRAY_SIZE(common_cmds) &&
		       (cmp = strcmp(common_cmds[n].name, candidate)) < 0)
			n++;
		if ((n < ARRAY_SIZE(common_cmds)) && !cmp) {
			/* Yes, this is one of the common commands */
			n++; /* use the entry from common_cmds[] */
			if (starts_with(candidate, cmd)) {
				/* Give prefix match a very good score */
				main_cmds.names[i]->len = 0;
				continue;
			}
		}

		main_cmds.names[i]->len =
			levenshtein(cmd, candidate, 0, 2, 1, 3) + 1;
	}

	QSORT(main_cmds.names, main_cmds.cnt, levenshtein_compare);

	if (!main_cmds.cnt)
		die(_("Uh oh. Your system reports no Git commands at all."));

	/* skip and count prefix matches */
	for (n = 0; n < main_cmds.cnt && !main_cmds.names[n]->len; n++)
		; /* still counting */

	if (main_cmds.cnt <= n) {
		/* prefix matches with everything? that is too ambiguous */
		best_similarity = SIMILARITY_FLOOR + 1;
	} else {
		/* count all the most similar ones */
		for (best_similarity = main_cmds.names[n++]->len;
		     (n < main_cmds.cnt &&
		      best_similarity == main_cmds.names[n]->len);
		     n++)
			; /* still counting */
	}
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

	if (SIMILAR_ENOUGH(best_similarity)) {
		fprintf_ln(stderr,
			   Q_("\nDid you mean this?",
			      "\nDid you mean one of these?",
			   n));

		for (i = 0; i < n; i++)
			fprintf(stderr, "\t%s\n", main_cmds.names[i]->name);
	}

	exit(1);
}