static int mark_seen(struct commit *commit, struct commit_list **seen_p)
{
	if (!commit->object.flags) {
		commit_list_insert(commit, seen_p);
		return 1;
	}
	return 0;
}