static int process_commit(struct walker *walker, struct commit *commit)
{
	if (parse_commit(commit))
		return -1;

	while (complete && complete->item->date >= commit->date) {
		pop_most_recent_commit(&complete, COMPLETE);
	}

	if (commit->object.flags & COMPLETE)
		return 0;

	hashcpy(current_commit_sha1, commit->object.sha1);

	walker_say(walker, "walk %s\n", sha1_to_hex(commit->object.sha1));

	if (walker->get_tree) {
		if (process(walker, &commit->tree->object))
			return -1;
		if (!walker->get_all)
			walker->get_tree = 0;
	}
	if (walker->get_history) {
		struct commit_list *parents = commit->parents;
		for (; parents; parents = parents->next) {
			if (process(walker, &parents->item->object))
				return -1;
		}
	}
	return 0;
}