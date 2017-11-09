static int is_final_fixup(struct todo_list *todo_list)
{
	int i = todo_list->current;

	if (!is_fixup(todo_list->items[i].command))
		return 0;

	while (++i < todo_list->nr)
		if (is_fixup(todo_list->items[i].command))
			return 0;
		else if (!is_noop(todo_list->items[i].command))
			break;
	return 1;
}