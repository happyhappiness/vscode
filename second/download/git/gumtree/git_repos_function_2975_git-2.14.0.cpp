static void todo_list_release(struct todo_list *todo_list)
{
	strbuf_release(&todo_list->buf);
	FREE_AND_NULL(todo_list->items);
	todo_list->nr = todo_list->alloc = 0;
}