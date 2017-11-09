static enum todo_command peek_command(struct todo_list *todo_list, int offset)
{
	int i;

	for (i = todo_list->current + offset; i < todo_list->nr; i++)
		if (!is_noop(todo_list->items[i].command))
			return todo_list->items[i].command;

	return -1;
}