	 * Also if pathspec patterns are dependent, we're in big
	 * trouble as we test each one separately
	 */
	parse_pathspec(&ar_args->pathspec, 0,
		       PATHSPEC_PREFER_FULL,
		       "", pathspec);
	if (pathspec) {
		while (*pathspec) {
			if (**pathspec && !path_exists(ar_args->tree, *pathspec))
				die(_("pathspec '%s' did not match any files"), *pathspec);
			pathspec++;
		}
