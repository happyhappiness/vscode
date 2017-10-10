	free_commit_list(revs->previous_parents);
	revs->previous_parents = copy_commit_list(commit->parents);
}

static struct commit *get_revision_1(struct rev_info *revs)
{
	if (!revs->commits)
		return NULL;

	do {
		struct commit *commit = pop_commit(&revs->commits);

		if (revs->reflog_info) {
			save_parents(revs, commit);
			fake_reflog_parent(revs->reflog_info, commit);
			commit->object.flags &= ~(ADDED | SEEN | SHOWN);
		}

		/*
		 * If we haven't done the list limiting, we need to look at
		 * the parents here. We also need to do the date-based limiting
		 * that we'd otherwise have done in limit_list().
		 */
		if (!revs->limited) {
			if (revs->max_age != -1 &&
			    (commit->date < revs->max_age))
				continue;
			if (add_parents_to_list(revs, commit, &revs->commits, NULL) < 0) {
				if (!revs->ignore_missing_links)
					die("Failed to traverse parents of commit %s",
						oid_to_hex(&commit->object.oid));
			}
		}

