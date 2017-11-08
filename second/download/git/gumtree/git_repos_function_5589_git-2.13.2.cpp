static void log_show_early(struct rev_info *revs, struct commit_list *list)
{
	int i = revs->early_output, close_file = revs->diffopt.close_file;
	int show_header = 1;

	revs->diffopt.close_file = 0;
	sort_in_topological_order(&list, revs->sort_order);
	while (list && i) {
		struct commit *commit = list->item;
		switch (simplify_commit(revs, commit)) {
		case commit_show:
			if (show_header) {
				int n = estimate_commit_count(revs, list);
				show_early_header(revs, "incomplete", n);
				show_header = 0;
			}
			log_tree_commit(revs, commit);
			i--;
			break;
		case commit_ignore:
			break;
		case commit_error:
			if (close_file)
				fclose(revs->diffopt.file);
			return;
		}
		list = list->next;
	}

	/* Did we already get enough commits for the early output? */
	if (!i) {
		if (close_file)
			fclose(revs->diffopt.file);
		return;
	}

	/*
	 * ..if no, then repeat it twice a second until we
	 * do.
	 *
	 * NOTE! We don't use "it_interval", because if the
	 * reader isn't listening, we want our output to be
	 * throttled by the writing, and not have the timer
	 * trigger every second even if we're blocked on a
	 * reader!
	 */
	early_output_timer.it_value.tv_sec = 0;
	early_output_timer.it_value.tv_usec = 500000;
	setitimer(ITIMER_REAL, &early_output_timer, NULL);
}