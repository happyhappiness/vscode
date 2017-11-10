static void wt_status_collect_untracked(struct wt_status *s)
{
	int i;
	struct dir_struct dir;
	uint64_t t_begin = getnanotime();

	if (!s->show_untracked_files)
		return;

	memset(&dir, 0, sizeof(dir));
	if (s->show_untracked_files != SHOW_ALL_UNTRACKED_FILES)
		dir.flags |=
			DIR_SHOW_OTHER_DIRECTORIES | DIR_HIDE_EMPTY_DIRECTORIES;
	if (s->show_ignored_files)
		dir.flags |= DIR_SHOW_IGNORED_TOO;
	setup_standard_excludes(&dir);

	fill_directory(&dir, &s->pathspec);

	for (i = 0; i < dir.nr; i++) {
		struct dir_entry *ent = dir.entries[i];
		if (cache_name_is_other(ent->name, ent->len) &&
		    dir_path_match(ent, &s->pathspec, 0, NULL))
			string_list_insert(&s->untracked, ent->name);
		free(ent);
	}

	for (i = 0; i < dir.ignored_nr; i++) {
		struct dir_entry *ent = dir.ignored[i];
		if (cache_name_is_other(ent->name, ent->len) &&
		    dir_path_match(ent, &s->pathspec, 0, NULL))
			string_list_insert(&s->ignored, ent->name);
		free(ent);
	}

	free(dir.entries);
	free(dir.ignored);
	clear_directory(&dir);

	if (advice_status_u_option)
		s->untracked_in_ms = (getnanotime() - t_begin) / 1000000;
}