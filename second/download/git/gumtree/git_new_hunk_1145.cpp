	}

	fprintf_ln(stderr, _("git: '%s' is not a git command. See 'git --help'."), cmd);

	if (SIMILAR_ENOUGH(best_similarity)) {
		fprintf_ln(stderr,
			   Q_("\nThe most similar command is",
			      "\nThe most similar commands are",
			   n));

		for (i = 0; i < n; i++)
			fprintf(stderr, "\t%s\n", main_cmds.names[i]->name);
	}

