static int grep_directory(struct grep_opt *opt, const struct pathspec *pathspec,
			  int exc_std, int use_index)
{
	struct dir_struct dir;
	int i, hit = 0;

	memset(&dir, 0, sizeof(dir));
	if (!use_index)
		dir.flags |= DIR_NO_GITLINKS;
	if (exc_std)
		setup_standard_excludes(&dir);

	fill_directory(&dir, &the_index, pathspec);
	for (i = 0; i < dir.nr; i++) {
		if (!dir_path_match(dir.entries[i], pathspec, 0, NULL))
			continue;
		hit |= grep_file(opt, dir.entries[i]->name);
		if (hit && opt->status_only)
			break;
	}
	return hit;
}