static void redo_list_add(int num)
{
	struct redo_list *rl;

	if (!(rl = new(struct redo_list)))
		exit_cleanup(RERR_MALLOC);
	rl->next = NULL;
	rl->num = num;
	if (redo_list_tail)
		redo_list_tail->next = rl;
	else
		redo_list_head = rl;
	redo_list_tail = rl;
}