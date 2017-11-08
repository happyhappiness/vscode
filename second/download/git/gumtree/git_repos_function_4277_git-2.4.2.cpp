static void add_remove_files(struct string_list *list)
{
	int i;
	for (i = 0; i < list->nr; i++) {
		struct stat st;
		struct string_list_item *p = &(list->items[i]);

		/* p->util is skip-worktree */
		if (p->util)
			continue;

		if (!lstat(p->string, &st)) {
			if (add_to_cache(p->string, &st, 0))
				die(_("updating files failed"));
		} else
			remove_file_from_cache(p->string);
	}
}