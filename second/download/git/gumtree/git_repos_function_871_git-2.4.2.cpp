static void cherry_pick_list(struct commit_list *list, struct rev_info *revs)
{
	struct commit_list *p;
	int left_count = 0, right_count = 0;
	int left_first;
	struct patch_ids ids;
	unsigned cherry_flag;

	/* First count the commits on the left and on the right */
	for (p = list; p; p = p->next) {
		struct commit *commit = p->item;
		unsigned flags = commit->object.flags;
		if (flags & BOUNDARY)
			;
		else if (flags & SYMMETRIC_LEFT)
			left_count++;
		else
			right_count++;
	}

	if (!left_count || !right_count)
		return;

	left_first = left_count < right_count;
	init_patch_ids(&ids);
	ids.diffopts.pathspec = revs->diffopt.pathspec;

	/* Compute patch-ids for one side */
	for (p = list; p; p = p->next) {
		struct commit *commit = p->item;
		unsigned flags = commit->object.flags;

		if (flags & BOUNDARY)
			continue;
		/*
		 * If we have fewer left, left_first is set and we omit
		 * commits on the right branch in this loop.  If we have
		 * fewer right, we skip the left ones.
		 */
		if (left_first != !!(flags & SYMMETRIC_LEFT))
			continue;
		commit->util = add_commit_patch_id(commit, &ids);
	}

	/* either cherry_mark or cherry_pick are true */
	cherry_flag = revs->cherry_mark ? PATCHSAME : SHOWN;

	/* Check the other side */
	for (p = list; p; p = p->next) {
		struct commit *commit = p->item;
		struct patch_id *id;
		unsigned flags = commit->object.flags;

		if (flags & BOUNDARY)
			continue;
		/*
		 * If we have fewer left, left_first is set and we omit
		 * commits on the left branch in this loop.
		 */
		if (left_first == !!(flags & SYMMETRIC_LEFT))
			continue;

		/*
		 * Have we seen the same patch id?
		 */
		id = has_commit_patch_id(commit, &ids);
		if (!id)
			continue;
		id->seen = 1;
		commit->object.flags |= cherry_flag;
	}

	/* Now check the original side for seen ones */
	for (p = list; p; p = p->next) {
		struct commit *commit = p->item;
		struct patch_id *ent;

		ent = commit->util;
		if (!ent)
			continue;
		if (ent->seen)
			commit->object.flags |= cherry_flag;
		commit->util = NULL;
	}

	free_patch_ids(&ids);
}