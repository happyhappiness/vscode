static void commit_list_set_next(void *a, void *next)
{
	((struct commit_list *)a)->next = next;
}