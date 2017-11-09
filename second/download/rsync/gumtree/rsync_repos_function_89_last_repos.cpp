static int rule_matches(const char *fname, filter_rule *ex, int name_is_dir)
{
	int slash_handling, str_cnt = 0, anchored_match = 0;
	int ret_match = ex->rflags & FILTRULE_NEGATE ? 0 : 1;
	char *p, *pattern = ex->pattern;
	const char *strings[16]; /* more than enough */
	const char *name = fname + (*fname == '/');

	if (!*name)
		return 0;

	if (!ex->u.slash_cnt && !(ex->rflags & FILTRULE_WILD2)) {
		/* If the pattern does not have any slashes AND it does
		 * not have a "**" (which could match a slash), then we
		 * just match the name portion of the path. */
		if ((p = strrchr(name,'/')) != NULL)
			name = p+1;
	} else if (ex->rflags & FILTRULE_ABS_PATH && *fname != '/'
	    && curr_dir_len > module_dirlen + 1) {
		/* If we're matching against an absolute-path pattern,
		 * we need to prepend our full path info. */
		strings[str_cnt++] = curr_dir + module_dirlen + 1;
		strings[str_cnt++] = "/";
	} else if (ex->rflags & FILTRULE_WILD2_PREFIX && *fname != '/') {
		/* Allow "**"+"/" to match at the start of the string. */
		strings[str_cnt++] = "/";
	}
	strings[str_cnt++] = name;
	if (name_is_dir) {
		/* Allow a trailing "/"+"***" to match the directory. */
		if (ex->rflags & FILTRULE_WILD3_SUFFIX)
			strings[str_cnt++] = "/";
	} else if (ex->rflags & FILTRULE_DIRECTORY)
		return !ret_match;
	strings[str_cnt] = NULL;

	if (*pattern == '/') {
		anchored_match = 1;
		pattern++;
	}

	if (!anchored_match && ex->u.slash_cnt
	    && !(ex->rflags & FILTRULE_WILD2)) {
		/* A non-anchored match with an infix slash and no "**"
		 * needs to match the last slash_cnt+1 name elements. */
		slash_handling = ex->u.slash_cnt + 1;
	} else if (!anchored_match && !(ex->rflags & FILTRULE_WILD2_PREFIX)
				   && ex->rflags & FILTRULE_WILD2) {
		/* A non-anchored match with an infix or trailing "**" (but not
		 * a prefixed "**") needs to try matching after every slash. */
		slash_handling = -1;
	} else {
		/* The pattern matches only at the start of the path or name. */
		slash_handling = 0;
	}

	if (ex->rflags & FILTRULE_WILD) {
		if (wildmatch_array(pattern, strings, slash_handling))
			return ret_match;
	} else if (str_cnt > 1) {
		if (litmatch_array(pattern, strings, slash_handling))
			return ret_match;
	} else if (anchored_match) {
		if (strcmp(name, pattern) == 0)
			return ret_match;
	} else {
		int l1 = strlen(name);
		int l2 = strlen(pattern);
		if (l2 <= l1 &&
		    strcmp(name+(l1-l2),pattern) == 0 &&
		    (l1==l2 || name[l1-(l2+1)] == '/')) {
			return ret_match;
		}
	}

	return !ret_match;
}