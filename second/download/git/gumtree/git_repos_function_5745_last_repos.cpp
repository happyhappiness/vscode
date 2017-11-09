static void add_merge_config(struct ref **head,
			   const struct ref *remote_refs,
		           struct branch *branch,
		           struct ref ***tail)
{
	int i;

	for (i = 0; i < branch->merge_nr; i++) {
		struct ref *rm, **old_tail = *tail;
		struct refspec refspec;

		for (rm = *head; rm; rm = rm->next) {
			if (branch_merge_matches(branch, i, rm->name)) {
				rm->fetch_head_status = FETCH_HEAD_MERGE;
				break;
			}
		}
		if (rm)
			continue;

		/*
		 * Not fetched to a remote-tracking branch?  We need to fetch
		 * it anyway to allow this branch's "branch.$name.merge"
		 * to be honored by 'git pull', but we do not have to
		 * fail if branch.$name.merge is misconfigured to point
		 * at a nonexisting branch.  If we were indeed called by
		 * 'git pull', it will notice the misconfiguration because
		 * there is no entry in the resulting FETCH_HEAD marked
		 * for merging.
		 */
		memset(&refspec, 0, sizeof(refspec));
		refspec.src = branch->merge[i]->src;
		get_fetch_map(remote_refs, &refspec, tail, 1);
		for (rm = *old_tail; rm; rm = rm->next)
			rm->fetch_head_status = FETCH_HEAD_MERGE;
	}
}