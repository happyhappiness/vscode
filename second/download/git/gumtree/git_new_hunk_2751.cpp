		bottom = collect_bottom_commits(list);
		if (!bottom)
			die("--ancestry-path given but there are no bottom commits");
	}

	while (list) {
		struct commit *commit = pop_commit(&list);
		struct object *obj = &commit->object;
		show_early_output_fn_t show;

		if (commit == interesting_cache)
			interesting_cache = NULL;

		if (revs->max_age != -1 && (commit->date < revs->max_age))
			obj->flags |= UNINTERESTING;
		if (add_parents_to_list(revs, commit, &list, NULL) < 0)
