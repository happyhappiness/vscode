static enum path_treatment read_directory_recursive(struct dir_struct *dir,
				    const char *base, int baselen,
				    int check_only,
				    const struct path_simplify *simplify)
{
	DIR *fdir;
	enum path_treatment state, subdir_state, dir_state = path_none;
	struct dirent *de;
	struct strbuf path = STRBUF_INIT;

	strbuf_add(&path, base, baselen);

	fdir = opendir(path.len ? path.buf : ".");
	if (!fdir)
		goto out;

	while ((de = readdir(fdir)) != NULL) {
		/* check how the file or directory should be treated */
		state = treat_path(dir, de, &path, baselen, simplify);
		if (state > dir_state)
			dir_state = state;

		/* recurse into subdir if instructed by treat_path */
		if (state == path_recurse) {
			subdir_state = read_directory_recursive(dir, path.buf,
				path.len, check_only, simplify);
			if (subdir_state > dir_state)
				dir_state = subdir_state;
		}

		if (check_only) {
			/* abort early if maximum state has been reached */
			if (dir_state == path_untracked)
				break;
			/* skip the dir_add_* part */
			continue;
		}

		/* add the path to the appropriate result list */
		switch (state) {
		case path_excluded:
			if (dir->flags & DIR_SHOW_IGNORED)
				dir_add_name(dir, path.buf, path.len);
			else if ((dir->flags & DIR_SHOW_IGNORED_TOO) ||
				((dir->flags & DIR_COLLECT_IGNORED) &&
				exclude_matches_pathspec(path.buf, path.len,
					simplify)))
				dir_add_ignored(dir, path.buf, path.len);
			break;

		case path_untracked:
			if (!(dir->flags & DIR_SHOW_IGNORED))
				dir_add_name(dir, path.buf, path.len);
			break;

		default:
			break;
		}
	}
	closedir(fdir);
 out:
	strbuf_release(&path);

	return dir_state;
}