static void unmark_and_free(struct commit_list *list, unsigned int mark)
{
	while (list) {
		struct commit_list *temp = list;
		temp->item->object.flags &= ~mark;
		list = temp->next;
		free(temp);
	}
}