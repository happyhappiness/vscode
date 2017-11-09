struct ref *find_ref_by_name(const struct ref *list, const char *name)
{
	for ( ; list; list = list->next)
		if (!strcmp(list->name, name))
			return (struct ref *)list;
	return NULL;
}