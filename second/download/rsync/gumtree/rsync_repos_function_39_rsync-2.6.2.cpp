static void report_exclude_result(char const *name,
                                  struct exclude_struct const *ent,
                                  int name_is_dir, const char *type)
{
	/* If a trailing slash is present to match only directories,
	 * then it is stripped out by make_exclude.  So as a special
	 * case we add it back in here. */

	if (verbose >= 2) {
		rprintf(FINFO, "[%s] %scluding %s %s because of %spattern %s%s\n",
			who_am_i(), ent->include ? "in" : "ex",
			name_is_dir ? "directory" : "file", name, type,
			ent->pattern, ent->directory ? "/" : "");
	}
}