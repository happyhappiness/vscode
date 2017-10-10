		fprintf(stderr, _("traversed %lu commits\n"), seen_commits);
		if (gave_up_on) {
			fprintf(stderr,
				_("more than %i tags found; listed %i most recent\n"
				"gave up search at %s\n"),
				max_candidates, max_candidates,
				sha1_to_hex(gave_up_on->object.sha1));
		}
	}

	display_name(all_matches[0].name);
	if (abbrev)
		show_suffix(all_matches[0].depth, cmit->object.sha1);
	if (dirty)
		printf("%s", dirty);
	printf("\n");

	if (!last_one)
		clear_commit_marks(cmit, -1);
