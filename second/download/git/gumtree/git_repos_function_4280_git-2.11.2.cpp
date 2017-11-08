static const unsigned char *get_rev(void)
{
	struct commit *commit = NULL;

	while (commit == NULL) {
		unsigned int mark;
		struct commit_list *parents;

		if (rev_list.nr == 0 || non_common_revs == 0)
			return NULL;

		commit = prio_queue_get(&rev_list);
		parse_commit(commit);
		parents = commit->parents;

		commit->object.flags |= POPPED;
		if (!(commit->object.flags & COMMON))
			non_common_revs--;

		if (commit->object.flags & COMMON) {
			/* do not send "have", and ignore ancestors */
			commit = NULL;
			mark = COMMON | SEEN;
		} else if (commit->object.flags & COMMON_REF)
			/* send "have", and ignore ancestors */
			mark = COMMON | SEEN;
		else
			/* send "have", also for its ancestors */
			mark = SEEN;

		while (parents) {
			if (!(parents->item->object.flags & SEEN))
				rev_list_push(parents->item, mark);
			if (mark & COMMON)
				mark_common(parents->item, 1, 0);
			parents = parents->next;
		}
	}

	return commit->object.oid.hash;
}