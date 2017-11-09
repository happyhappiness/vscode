int query_refspecs(struct refspec *refs, int ref_count, struct refspec *query)
{
	int i;
	int find_src = !query->src;
	const char *needle = find_src ? query->dst : query->src;
	char **result = find_src ? &query->src : &query->dst;

	if (find_src && !query->dst)
		return error("query_refspecs: need either src or dst");

	for (i = 0; i < ref_count; i++) {
		struct refspec *refspec = &refs[i];
		const char *key = find_src ? refspec->dst : refspec->src;
		const char *value = find_src ? refspec->src : refspec->dst;

		if (!refspec->dst)
			continue;
		if (refspec->pattern) {
			if (match_name_with_pattern(key, needle, value, result)) {
				query->force = refspec->force;
				return 0;
			}
		} else if (!strcmp(needle, key)) {
			*result = xstrdup(value);
			query->force = refspec->force;
			return 0;
		}
	}
	return -1;
}