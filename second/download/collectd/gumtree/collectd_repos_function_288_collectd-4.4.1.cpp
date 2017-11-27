static procstat_t *ps_list_search (const char *name)
{
	procstat_t *ptr;

	for (ptr = list_head_g; ptr != NULL; ptr = ptr->next)
		if (strcmp (ptr->name, name) == 0)
			break;

	return (ptr);
}