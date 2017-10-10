}

static int merge_trivial(struct commit *head, struct commit_list *remoteheads)
{
	unsigned char result_tree[20], result_commit[20];
	struct commit_list *parents, **pptr = &parents;

	write_tree_trivial(result_tree);
	printf(_("Wonderful.\n"));
	pptr = commit_list_append(head, pptr);
	pptr = commit_list_append(remoteheads->item, pptr);
	prepare_to_commit(remoteheads);
