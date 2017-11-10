void clear_commit_marks_many(int nr, struct commit **commit, unsigned int mark)
{
	struct commit_list *list = NULL;

	while (nr--) {
		commit_list_insert(*commit, &list);
		commit++;
	}
	while (list)
		clear_commit_marks_1(&list, pop_commit(&list), mark);
}