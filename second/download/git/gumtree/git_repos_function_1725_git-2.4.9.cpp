static int fill(const char *path, int pathlen, int basename_offset,
		struct attr_stack *stk, int rem)
{
	int i;
	const char *base = stk->origin ? stk->origin : "";

	for (i = stk->num_matches - 1; 0 < rem && 0 <= i; i--) {
		struct match_attr *a = stk->attrs[i];
		if (a->is_macro)
			continue;
		if (path_matches(path, pathlen, basename_offset,
				 &a->u.pat, base, stk->originlen))
			rem = fill_one("fill", a, rem);
	}
	return rem;
}