static void report_filter_result(enum logcode code, char const *name,
				 filter_rule const *ent,
				 int name_is_dir, const char *type)
{
	/* If a trailing slash is present to match only directories,
	 * then it is stripped out by add_rule().  So as a special
	 * case we add it back in here. */

	if (DEBUG_GTE(FILTER, 1)) {
		static char *actions[2][2]
		    = { {"show", "hid"}, {"risk", "protect"} };
		const char *w = who_am_i();
		rprintf(code, "[%s] %sing %s %s because of pattern %s%s%s\n",
		    w, actions[*w!='s'][!(ent->rflags & FILTRULE_INCLUDE)],
		    name_is_dir ? "directory" : "file", name, ent->pattern,
		    ent->rflags & FILTRULE_DIRECTORY ? "/" : "", type);
	}
}