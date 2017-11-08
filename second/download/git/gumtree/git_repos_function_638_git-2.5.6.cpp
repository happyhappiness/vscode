struct commit *pop_most_recent_commit(struct commit_list **list,
				      unsigned int mark)
{
	struct commit *ret = (*list)->item;
	struct commit_list *parents = ret->parents;
	struct commit_list *old = *list;

	*list = (*list)->next;
	free(old);

	while (parents) {
		struct commit *commit = parents->item;
		if (!parse_commit(commit) && !(commit->object.flags & mark)) {
			commit->object.flags |= mark;
			commit_list_insert_by_date(commit, list);
		}
		parents = parents->next;
	}
	return ret;
}