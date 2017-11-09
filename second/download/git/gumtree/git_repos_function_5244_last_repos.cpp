static int check_ignore(struct dir_struct *dir,
			const char *prefix, int argc, const char **argv)
{
	const char *full_path;
	char *seen;
	int num_ignored = 0, dtype = DT_UNKNOWN, i;
	struct exclude *exclude;
	struct pathspec pathspec;

	if (!argc) {
		if (!quiet)
			fprintf(stderr, "no pathspec given.\n");
		return 0;
	}

	/*
	 * check-ignore just needs paths. Magic beyond :/ is really
	 * irrelevant.
	 */
	parse_pathspec(&pathspec,
		       PATHSPEC_ALL_MAGIC & ~PATHSPEC_FROMTOP,
		       PATHSPEC_SYMLINK_LEADING_PATH |
		       PATHSPEC_KEEP_ORDER,
		       prefix, argv);

	die_path_inside_submodule(&the_index, &pathspec);

	/*
	 * look for pathspecs matching entries in the index, since these
	 * should not be ignored, in order to be consistent with
	 * 'git status', 'git add' etc.
	 */
	seen = find_pathspecs_matching_against_index(&pathspec, &the_index);
	for (i = 0; i < pathspec.nr; i++) {
		full_path = pathspec.items[i].match;
		exclude = NULL;
		if (!seen[i]) {
			exclude = last_exclude_matching(dir, &the_index,
							full_path, &dtype);
		}
		if (!quiet && (exclude || show_non_matching))
			output_exclude(pathspec.items[i].original, exclude);
		if (exclude)
			num_ignored++;
	}
	free(seen);

	return num_ignored;
}