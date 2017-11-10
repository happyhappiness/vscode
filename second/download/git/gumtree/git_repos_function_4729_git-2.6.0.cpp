static void show_ru_info(void)
{
	struct string_list_item *item;

	if (!the_index.resolve_undo)
		return;

	for_each_string_list_item(item, the_index.resolve_undo) {
		const char *path = item->string;
		struct resolve_undo_info *ui = item->util;
		int i, len;

		len = strlen(path);
		if (len < max_prefix_len)
			continue; /* outside of the prefix */
		if (!match_pathspec(&pathspec, path, len,
				    max_prefix_len, ps_matched, 0))
			continue; /* uninterested */
		for (i = 0; i < 3; i++) {
			if (!ui->mode[i])
				continue;
			printf("%s%06o %s %d\t", tag_resolve_undo, ui->mode[i],
			       find_unique_abbrev(ui->sha1[i], abbrev),
			       i + 1);
			write_name(path);
		}
	}
}