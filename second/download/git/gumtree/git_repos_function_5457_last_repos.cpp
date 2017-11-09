static void chmod_pathspec(struct pathspec *pathspec, char flip)
{
	int i;

	for (i = 0; i < active_nr; i++) {
		struct cache_entry *ce = active_cache[i];

		if (pathspec && !ce_path_match(ce, pathspec, NULL))
			continue;

		if (chmod_cache_entry(ce, flip) < 0)
			fprintf(stderr, "cannot chmod %cx '%s'\n", flip, ce->name);
	}
}