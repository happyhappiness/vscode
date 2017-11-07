static struct commit *get_base_commit(const char *base_commit,
				      struct commit **list,
				      int total)
{
	struct commit *base = NULL;
	struct commit **rev;
	int i = 0, rev_nr = 0;

	if (base_commit && strcmp(base_commit, "auto")) {
		base = lookup_commit_reference_by_name(base_commit);
		if (!base)
			die(_("Unknown commit %s"), base_commit);
	} else if ((base_commit && !strcmp(base_commit, "auto")) || base_auto) {
		struct branch *curr_branch = branch_get(NULL);
		const char *upstream = branch_get_upstream(curr_branch, NULL);
		if (upstream) {
			struct commit_list *base_list;
			struct commit *commit;
			unsigned char sha1[20];

			if (get_sha1(upstream, sha1))
				die(_("Failed to resolve '%s' as a valid ref."), upstream);
			commit = lookup_commit_or_die(sha1, "upstream base");
			base_list = get_merge_bases_many(commit, total, list);
			/* There should be one and only one merge base. */
			if (!base_list || base_list->next)
				die(_("Could not find exact merge base."));
			base = base_list->item;
			free_commit_list(base_list);
		} else {
			die(_("Failed to get upstream, if you want to record base commit automatically,\n"
			      "please use git branch --set-upstream-to to track a remote branch.\n"
			      "Or you could specify base commit by --base=<base-commit-id> manually."));
		}
	}

	ALLOC_ARRAY(rev, total);
	for (i = 0; i < total; i++)
		rev[i] = list[i];

	rev_nr = total;
	/*
	 * Get merge base through pair-wise computations
	 * and store it in rev[0].
	 */
	while (rev_nr > 1) {
		for (i = 0; i < rev_nr / 2; i++) {
			struct commit_list *merge_base;
			merge_base = get_merge_bases(rev[2 * i], rev[2 * i + 1]);
			if (!merge_base || merge_base->next)
				die(_("Failed to find exact merge base"));

			rev[i] = merge_base->item;
		}

		if (rev_nr % 2)
			rev[i] = rev[2 * i];
		rev_nr = (rev_nr + 1) / 2;
	}

	if (!in_merge_bases(base, rev[0]))
		die(_("base commit should be the ancestor of revision list"));

	for (i = 0; i < total; i++) {
		if (base == list[i])
			die(_("base commit shouldn't be in revision list"));
	}

	free(rev);
	return base;
}