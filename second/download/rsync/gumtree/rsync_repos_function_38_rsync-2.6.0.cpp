static void report_exclude_result(char const *name,
                                  struct exclude_struct const *ent,
                                  int name_is_dir)
{
	/* If a trailing slash is present to match only directories,
	 * then it is stripped out by make_exclude.  So as a special
	 * case we add it back in here. */

	if (verbose >= 2)
		rprintf(FINFO, "%s %s %s because of pattern %s%s\n",
			ent->include ? "including" : "excluding",
			name_is_dir ? "directory" : "file",
			name, ent->pattern,
			ent->directory ? "/" : "");
}