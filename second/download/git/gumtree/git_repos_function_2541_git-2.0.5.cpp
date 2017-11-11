void schedule_dir_for_removal(const char *name, int len)
{
	int match_len, last_slash, i, previous_slash;

	match_len = last_slash = i =
		longest_path_match(name, len, removal.path, removal.len,
				   &previous_slash);
	/* Find last slash inside 'name' */
	while (i < len) {
		if (name[i] == '/')
			last_slash = i;
		i++;
	}

	/*
	 * If we are about to go down the directory tree, we check if
	 * we must first go upwards the tree, such that we then can
	 * remove possible empty directories as we go upwards.
	 */
	if (match_len < last_slash && match_len < removal.len)
		do_remove_scheduled_dirs(match_len);
	/*
	 * If we go deeper down the directory tree, we only need to
	 * save the new path components as we go down.
	 */
	if (match_len < last_slash) {
		memcpy(&removal.path[match_len], &name[match_len],
		       last_slash - match_len);
		removal.len = last_slash;
	}
}