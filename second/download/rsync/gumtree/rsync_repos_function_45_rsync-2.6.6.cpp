static void report_filter_result(char const *name,
                                 struct filter_struct const *ent,
                                 int name_is_dir, const char *type)
{
	/* If a trailing slash is present to match only directories,
	 * then it is stripped out by add_rule().  So as a special
	 * case we add it back in here. */

	if (verbose >= 2) {
		rprintf(FINFO, "[%s] %scluding %s %s because of pattern %s%s%s\n",
			who_am_i(),
			ent->match_flags & MATCHFLG_INCLUDE ? "in" : "ex",
			name_is_dir ? "directory" : "file", name, ent->pattern,
			ent->match_flags & MATCHFLG_DIRECTORY ? "/" : "", type);
	}
}