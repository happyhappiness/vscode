static void collect_some_attrs(const char *path, struct attr_check *check)
{
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

	prepare_attr_stack(path, dirlen, &check->stack);
	all_attrs_init(&g_attr_hashmap, check);
	determine_macros(check->all_attrs, check->stack);

	if (check->nr) {
		rem = 0;
		for (i = 0; i < check->nr; i++) {
			int n = check->items[i].attr->attr_nr;
			struct all_attrs_item *item = &check->all_attrs[n];
			if (item->macro) {
				item->value = ATTR__UNSET;
				rem++;
			}
		}
		if (rem == check->nr)
			return;
	}

	rem = check->all_attrs_nr;
	fill(path, pathlen, basename_offset, check->stack, check->all_attrs, rem);
}