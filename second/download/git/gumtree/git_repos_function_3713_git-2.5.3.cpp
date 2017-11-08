static void rev_list_push(struct commit *commit, int mark)
{
	if (!(commit->object.flags & mark)) {
		commit->object.flags |= mark;

		if (parse_commit(commit))
			return;

		prio_queue_put(&rev_list, commit);

		if (!(commit->object.flags & COMMON))
			non_common_revs++;
	}
}