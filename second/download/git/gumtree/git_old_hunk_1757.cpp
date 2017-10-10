	}
	return 0;
}

static int remove_branches(struct string_list *branches)
{
	const char **branch_names;
	int i, result = 0;

	branch_names = xmalloc(branches->nr * sizeof(*branch_names));
	for (i = 0; i < branches->nr; i++)
		branch_names[i] = branches->items[i].string;
	result |= repack_without_refs(branch_names, branches->nr, NULL);
	free(branch_names);

	for (i = 0; i < branches->nr; i++) {
		struct string_list_item *item = branches->items + i;
		const char *refname = item->string;

