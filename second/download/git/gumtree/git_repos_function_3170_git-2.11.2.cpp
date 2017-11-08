const char *find_descendant_ref(const char *dirname,
				const struct string_list *extras,
				const struct string_list *skip)
{
	int pos;

	if (!extras)
		return NULL;

	/*
	 * Look at the place where dirname would be inserted into
	 * extras. If there is an entry at that position that starts
	 * with dirname (remember, dirname includes the trailing
	 * slash) and is not in skip, then we have a conflict.
	 */
	for (pos = string_list_find_insert_index(extras, dirname, 0);
	     pos < extras->nr; pos++) {
		const char *extra_refname = extras->items[pos].string;

		if (!starts_with(extra_refname, dirname))
			break;

		if (!skip || !string_list_has_string(skip, extra_refname))
			return extra_refname;
	}
	return NULL;
}