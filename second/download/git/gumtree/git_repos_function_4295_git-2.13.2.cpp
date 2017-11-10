static void query_refspecs_multiple(struct refspec *refs, int ref_count, struct refspec *query, struct string_list *results)
{
	int i;
	int find_src = !query->src;

	if (find_src && !query->dst)
		error("query_refspecs_multiple: need either src or dst");

	for (i = 0; i < ref_count; i++) {
		struct refspec *refspec = &refs[i];
		const char *key = find_src ? refspec->dst : refspec->src;
		const char *value = find_src ? refspec->src : refspec->dst;
		const char *needle = find_src ? query->dst : query->src;
		char **result = find_src ? &query->src : &query->dst;

		if (!refspec->dst)
			continue;
		if (refspec->pattern) {
			if (match_name_with_pattern(key, needle, value, result))
				string_list_append_nodup(results, *result);
		} else if (!strcmp(needle, key)) {
			string_list_append(results, value);
		}
	}
}