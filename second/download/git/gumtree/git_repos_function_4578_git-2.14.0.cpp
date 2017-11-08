int delayed_reachability_test(struct shallow_info *si, int c)
{
	if (si->need_reachability_test[c]) {
		struct commit *commit = lookup_commit(&si->shallow->oid[c]);

		if (!si->commits) {
			struct commit_array ca;

			memset(&ca, 0, sizeof(ca));
			head_ref(add_ref, &ca);
			for_each_ref(add_ref, &ca);
			si->commits = ca.commits;
			si->nr_commits = ca.nr;
		}

		si->reachable[c] = in_merge_bases_many(commit,
						       si->nr_commits,
						       si->commits);
		si->need_reachability_test[c] = 0;
	}
	return si->reachable[c];
}