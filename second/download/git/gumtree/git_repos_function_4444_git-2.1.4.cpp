static struct commit *pop_one_commit(struct commit_list **list_p)
{
	struct commit *commit;
	struct commit_list *list;
	list = *list_p;
	commit = list->item;
	*list_p = list->next;
	free(list);
	return commit;
}