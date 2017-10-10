		 * Detached form ("--pretty X" as opposed to "--pretty=X")
		 * not allowed, since the argument is optional.
		 */
		revs->verbose_header = 1;
		revs->pretty_given = 1;
		get_commit_format(arg+9, revs);
	} else if (!strcmp(arg, "--show-notes") || !strcmp(arg, "--notes")) {
		revs->show_notes = 1;
		revs->show_notes_given = 1;
		revs->notes_opt.use_default_notes = 1;
	} else if (!strcmp(arg, "--show-signature")) {
		revs->show_signature = 1;
