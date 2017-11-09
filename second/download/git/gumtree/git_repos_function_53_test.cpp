int is_descendant_of(struct commit *commit, struct commit_list *with_commit)
{
	if (!with_commit)
		return 1;
	while (with_commit) {
		struct commit *other;

		other = with_commit->item;
		with_commit = with_commit->next;
		if (in_merge_bases(other, commit))
			return 1;
	}
	return 0;
}