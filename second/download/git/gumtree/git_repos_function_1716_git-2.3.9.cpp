static void collect_all_attrs(const char *path)
{
	struct attr_stack *stk;
	int i, pathlen, rem, dirlen;
	const char *cp, *last_slash = NULL;
	int basename_offset;

	for (cp = path; *cp; cp++) {
		if (*cp == '/' && cp[1])
			last_slash = cp;
	}
	pathlen = cp - path;
	if (last_slash) {
		basename_offset = last_slash + 1 - path;
		dirlen = last_slash - path;
	} else {
		basename_offset = 0;
		dirlen = 0;
	}

	prepare_attr_stack(path, dirlen);
	for (i = 0; i < attr_nr; i++)
		check_all_attr[i].value = ATTR__UNKNOWN;

	rem = attr_nr;
	for (stk = attr_stack; 0 < rem && stk; stk = stk->prev)
		rem = fill(path, pathlen, basename_offset, stk, rem);
}