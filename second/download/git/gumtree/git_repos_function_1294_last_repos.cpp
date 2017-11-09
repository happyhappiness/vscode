static struct commit *get_revision_1(struct rev_info *revs)
{
	while (1) {
		struct commit *commit;

		if (revs->reflog_info)
			commit = next_reflog_entry(revs->reflog_info);
		else
			commit = pop_commit(&revs->commits);

		if (!commit)
			return NULL;

		if (revs->reflog_info)
			commit->object.flags &= ~(ADDED | SEEN | SHOWN);

		/*
		 * If we haven't done the list limiting, we need to look at
		 * the parents here. We also need to do the date-based limiting
		 * that we'd otherwise have done in limit_list().
		 */
		if (!revs->limited) {
			if (revs->max_age != -1 &&
			    comparison_date(revs, commit) < revs->max_age)
				continue;

			if (revs->reflog_info)
				try_to_simplify_commit(revs, commit);
			else if (add_parents_to_list(revs, commit, &revs->commits, NULL) < 0) {
				if (!revs->ignore_missing_links)
					die("Failed to traverse parents of commit %s",
						oid_to_hex(&commit->object.oid));
			}
		}

		switch (simplify_commit(revs, commit)) {
		case commit_ignore:
			continue;
		case commit_error:
			die("Failed to simplify parents of commit %s",
			    oid_to_hex(&commit->object.oid));
		default:
			if (revs->track_linear)
				track_linear(revs, commit);
			return commit;
		}
	}
}