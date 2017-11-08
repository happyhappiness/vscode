static int rule_matches(char *name, struct filter_struct *ex, int name_is_dir)
{
	char *p, full_name[MAXPATHLEN];
	int match_start = 0;
	int ret_match = ex->match_flags & MATCHFLG_NEGATE ? 0 : 1;
	char *pattern = ex->pattern;

	if (!*name)
		return 0;

	/* If the pattern does not have any slashes AND it does not have
	 * a "**" (which could match a slash), then we just match the
	 * name portion of the path. */
	if (!ex->u.slash_cnt && !(ex->match_flags & MATCHFLG_WILD2)) {
		if ((p = strrchr(name,'/')) != NULL)
			name = p+1;
	}
	else if (ex->match_flags & MATCHFLG_ABS_PATH && *name != '/'
	    && curr_dir_len > module_dirlen + 1) {
		pathjoin(full_name, sizeof full_name,
			 curr_dir + module_dirlen + 1, name);
		name = full_name;
	}

	if (ex->match_flags & MATCHFLG_DIRECTORY && !name_is_dir)
		return !ret_match;

	if (*pattern == '/') {
		match_start = 1;
		pattern++;
		if (*name == '/')
			name++;
	}

	if (ex->match_flags & MATCHFLG_WILD) {
		/* A non-anchored match with an infix slash and no "**"
		 * needs to match the last slash_cnt+1 name elements. */
		if (!match_start && ex->u.slash_cnt
		    && !(ex->match_flags & MATCHFLG_WILD2)) {
			int cnt = ex->u.slash_cnt + 1;
			for (p = name + strlen(name) - 1; p >= name; p--) {
				if (*p == '/' && !--cnt)
					break;
			}
			name = p+1;
		}
		if (wildmatch(pattern, name))
			return ret_match;
		if (ex->match_flags & MATCHFLG_WILD2_PREFIX) {
			/* If the **-prefixed pattern has a '/' as the next
			 * character, then try to match the rest of the
			 * pattern at the root. */
			if (pattern[2] == '/' && wildmatch(pattern+3, name))
				return ret_match;
		}
		else if (!match_start && ex->match_flags & MATCHFLG_WILD2) {
			/* A non-anchored match with an infix or trailing "**"
			 * (but not a prefixed "**") needs to try matching
			 * after every slash. */
			while ((name = strchr(name, '/')) != NULL) {
				name++;
				if (wildmatch(pattern, name))
					return ret_match;
			}
		}
	} else if (match_start) {
		if (strcmp(name,pattern) == 0)
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