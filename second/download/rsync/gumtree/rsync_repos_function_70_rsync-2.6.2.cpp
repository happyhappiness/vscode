int get_redo_num(void)
{
	struct redo_list *next;
	int num;

	while (!redo_list_head)
		read_msg_fd();

	num = redo_list_head->num;
	next = redo_list_head->next;
	free(redo_list_head);
	redo_list_head = next;
	if (!next)
		redo_list_tail = NULL;

	return num;
}