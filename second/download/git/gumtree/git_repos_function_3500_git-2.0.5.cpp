void string_list_add_refs_from_colon_sep(struct string_list *list,
					 const char *globs)
{
	struct string_list split = STRING_LIST_INIT_NODUP;
	char *globs_copy = xstrdup(globs);
	int i;

	string_list_split_in_place(&split, globs_copy, ':', -1);
	string_list_remove_empty_items(&split, 0);

	for (i = 0; i < split.nr; i++)
		string_list_add_refs_by_glob(list, split.items[i].string);

	string_list_clear(&split, 0);
	free(globs_copy);
}