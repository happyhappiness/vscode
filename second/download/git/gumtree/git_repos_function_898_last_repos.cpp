static void *commit_list_get_next(const void *a)
{
	return ((const struct commit_list *)a)->next;
}