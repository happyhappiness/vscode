static void ref_list_set_next(void *a, void *next)
{
	((struct ref *)a)->next = next;
}