static int remove_branches(struct string_list *branches)
{
	struct strbuf err = STRBUF_INIT;
	const char **branch_names;
	int i, result = 0;

	branch_names = xmalloc(branches->nr * sizeof(*branch_names));
	for (i = 0; i < branches->nr; i++)
		branch_names[i] = branches->items[i].string;
	if (repack_without_refs(branch_names, branches->nr, &err))
		result |= error("%s", err.buf);
	strbuf_release(&err);
	free(branch_names);

	for (i = 0; i < branches->nr; i++) {
		struct string_list_item *item = branches->items + i;
		const char *refname = item->string;

		if (delete_ref(refname, NULL, 0))
			result |= error(_("Could not remove branch %s"), refname);
	}

	return result;
}