static int fill(const char *path, int pathlen, int basename_offset,
		const struct attr_stack *stack,
		struct all_attrs_item *all_attrs, int rem)
{
	for (; rem > 0 && stack; stack = stack->prev) {
		int i;
		const char *base = stack->origin ? stack->origin : "";

		for (i = stack->num_matches - 1; 0 < rem && 0 <= i; i--) {
			const struct match_attr *a = stack->attrs[i];
			if (a->is_macro)
				continue;
			if (path_matches(path, pathlen, basename_offset,
					 &a->u.pat, base, stack->originlen))
				rem = fill_one("fill", all_attrs, a, rem);
		}
	}

	return rem;
}