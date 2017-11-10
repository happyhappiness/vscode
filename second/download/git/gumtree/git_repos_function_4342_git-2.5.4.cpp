static struct ref_sort *default_sort(void)
{
	static const char cstr_name[] = "refname";

	struct ref_sort *sort = xcalloc(1, sizeof(*sort));

	sort->next = NULL;
	sort->atom = parse_atom(cstr_name, cstr_name + strlen(cstr_name));
	return sort;
}