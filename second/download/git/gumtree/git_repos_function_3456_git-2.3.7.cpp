static void *ref_list_get_next(const void *a)
{
	return ((const struct ref *)a)->next;
}