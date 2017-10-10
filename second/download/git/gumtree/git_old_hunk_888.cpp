		seen_commits--;
	}
	seen_commits += finish_depth_computation(&list, &all_matches[0]);
	free_commit_list(list);

	if (debug) {
		for (cur_match = 0; cur_match < match_cnt; cur_match++) {
			struct possible_tag *t = &all_matches[cur_match];
			fprintf(stderr, " %-11s %8d %s\n",
				prio_names[t->name->prio],
				t->depth, t->name->path);
		}
		fprintf(stderr, _("traversed %lu commits\n"), seen_commits);
		if (gave_up_on) {
			fprintf(stderr,
				_("more than %i tags found; listed %i most recent\n"
