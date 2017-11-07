static int process_ranges_merge_commit(struct rev_info *rev, struct commit *commit,
				       struct line_log_data *range)
{
	struct diff_queue_struct *diffqueues;
	struct line_log_data **cand;
	struct commit **parents;
	struct commit_list *p;
	int i;
	int nparents = commit_list_count(commit->parents);

	if (nparents > 1 && rev->first_parent_only)
		nparents = 1;

	ALLOC_ARRAY(diffqueues, nparents);
	ALLOC_ARRAY(cand, nparents);
	ALLOC_ARRAY(parents, nparents);

	p = commit->parents;
	for (i = 0; i < nparents; i++) {
		parents[i] = p->item;
		p = p->next;
		queue_diffs(range, &rev->diffopt, &diffqueues[i], commit, parents[i]);
	}

	for (i = 0; i < nparents; i++) {
		int changed;
		cand[i] = NULL;
		changed = process_all_files(&cand[i], rev, &diffqueues[i], range);
		if (!changed) {
			/*
			 * This parent can take all the blame, so we
			 * don't follow any other path in history
			 */
			add_line_range(rev, parents[i], cand[i]);
			clear_commit_line_range(rev, commit);
			commit_list_append(parents[i], &commit->parents);
			free(parents);
			free(cand);
			free_diffqueues(nparents, diffqueues);
			/* NEEDSWORK leaking like a sieve */
			return 0;
		}
	}

	/*
	 * No single parent took the blame.  We add the candidates
	 * from the above loop to the parents.
	 */
	for (i = 0; i < nparents; i++) {
		add_line_range(rev, parents[i], cand[i]);
	}

	clear_commit_line_range(rev, commit);
	free(parents);
	free(cand);
	free_diffqueues(nparents, diffqueues);
	return 1;

	/* NEEDSWORK evil merge detection stuff */
	/* NEEDSWORK leaking like a sieve */
}