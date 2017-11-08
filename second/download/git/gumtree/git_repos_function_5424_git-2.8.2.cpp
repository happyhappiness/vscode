static void parse_args(struct pathspec *pathspec,
		       const char **argv, const char *prefix,
		       int patch_mode,
		       const char **rev_ret)
{
	const char *rev = "HEAD";
	unsigned char unused[20];
	/*
	 * Possible arguments are:
	 *
	 * git reset [-opts] [<rev>]
	 * git reset [-opts] <tree> [<paths>...]
	 * git reset [-opts] <tree> -- [<paths>...]
	 * git reset [-opts] -- [<paths>...]
	 * git reset [-opts] <paths>...
	 *
	 * At this point, argv points immediately after [-opts].
	 */

	if (argv[0]) {
		if (!strcmp(argv[0], "--")) {
			argv++; /* reset to HEAD, possibly with paths */
		} else if (argv[1] && !strcmp(argv[1], "--")) {
			rev = argv[0];
			argv += 2;
		}
		/*
		 * Otherwise, argv[0] could be either <rev> or <paths> and
		 * has to be unambiguous. If there is a single argument, it
		 * can not be a tree
		 */
		else if ((!argv[1] && !get_sha1_committish(argv[0], unused)) ||
			 (argv[1] && !get_sha1_treeish(argv[0], unused))) {
			/*
			 * Ok, argv[0] looks like a commit/tree; it should not
			 * be a filename.
			 */
			verify_non_filename(prefix, argv[0]);
			rev = *argv++;
		} else {
			/* Otherwise we treat this as a filename */
			verify_filename(prefix, argv[0], 1);
		}
	}
	*rev_ret = rev;

	if (read_cache() < 0)
		die(_("index file corrupt"));

	parse_pathspec(pathspec, 0,
		       PATHSPEC_PREFER_FULL |
		       PATHSPEC_STRIP_SUBMODULE_SLASH_CHEAP |
		       (patch_mode ? PATHSPEC_PREFIX_ORIGIN : 0),
		       prefix, argv);
}