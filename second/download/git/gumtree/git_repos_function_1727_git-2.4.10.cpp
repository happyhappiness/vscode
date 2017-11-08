static void collect_some_attrs(const char *path, int num,
			       struct git_attr_check *check)

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
	if (num && !cannot_trust_maybe_real) {
		rem = 0;
		for (i = 0; i < num; i++) {
			if (!check[i].attr->maybe_real) {
				struct git_attr_check *c;
				c = check_all_attr + check[i].attr->attr_nr;
				c->value = ATTR__UNSET;
				rem++;
			}
		}
		if (rem == num)
			return;
	}

	rem = attr_nr;
	for (stk = attr_stack; 0 < rem && stk; stk = stk->prev)
		rem = fill(path, pathlen, basename_offset, stk, rem);
}