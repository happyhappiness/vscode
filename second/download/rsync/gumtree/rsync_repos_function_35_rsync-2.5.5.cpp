static int check_one_exclude(char *name, struct exclude_struct *ex,
                             STRUCT_STAT *st)
{
	char *p;
	int match_start=0;
	char *pattern = ex->pattern;

	if (ex->local && (p=strrchr(name,'/')))
		name = p+1;

	if (!name[0]) return 0;

	if (ex->directory && !S_ISDIR(st->st_mode)) return 0;

	if (*pattern == '/' && *name != '/') {
		match_start = 1;
		pattern++;
	}

	if (ex->regular_exp) {
		if (fnmatch(pattern, name, ex->fnmatch_flags) == 0) {
			return 1;
		}
	} else {
		int l1 = strlen(name);
		int l2 = strlen(pattern);
		if (l2 <= l1 && 
		    strcmp(name+(l1-l2),pattern) == 0 &&
		    (l1==l2 || (!match_start && name[l1-(l2+1)] == '/'))) {
			return 1;
		}
	}

	return 0;
}