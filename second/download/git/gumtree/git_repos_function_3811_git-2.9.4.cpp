static void unmark_and_free(struct commit_list *list, unsigned int mark)
{
	while (list) {
		struct commit *commit = pop_commit(&list);
		commit->object.flags &= ~mark;
	}
}