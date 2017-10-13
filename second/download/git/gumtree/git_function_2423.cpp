tatic int list_tags(const char **patterns, int lines,
		     struct commit_list *with_commit, int sort)
{
	struct tag_filter filter;

	filter.patterns = patterns;
	filter.lines = lines;
	filter.sort = sort;
	filter.with_commit = with_commit;
	memset(&filter.tags, 0, sizeof(filter.tags));
	filter.tags.strdup_strings = 1;

	for_each_tag_ref(show_reference, (void *)&filter);
	if (sort) {
		int i;
		if ((sort & SORT_MASK) == VERCMP_SORT)
			qsort(filter.tags.items, filter.tags.nr,
			      sizeof(struct string_list_item), sort_by_version);
		if (sort & REVERSE_SORT)
			for (i = filter.tags.nr - 1; i >= 0; i--)
				printf("%s\n", filter.tags.items[i].string);
		else
			for (i = 0; i < filter.tags.nr; i++)
				printf("%s\n", filter.tags.items[i].string);
		string_list_clear(&filter.tags, 0);
	}
	return 0;
}