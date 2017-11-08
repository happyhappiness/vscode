static int use_patch(struct patch *p)
{
	const char *pathname = p->new_name ? p->new_name : p->old_name;
	int i;

	/* Paths outside are not touched regardless of "--include" */
	if (0 < prefix_length) {
		int pathlen = strlen(pathname);
		if (pathlen <= prefix_length ||
		    memcmp(prefix, pathname, prefix_length))
			return 0;
	}

	/* See if it matches any of exclude/include rule */
	for (i = 0; i < limit_by_name.nr; i++) {
		struct string_list_item *it = &limit_by_name.items[i];
		if (!wildmatch(it->string, pathname, 0, NULL))
			return (it->util != NULL);
	}

	/*
	 * If we had any include, a path that does not match any rule is
	 * not used.  Otherwise, we saw bunch of exclude rules (or none)
	 * and such a path is used.
	 */
	return !has_include;
}