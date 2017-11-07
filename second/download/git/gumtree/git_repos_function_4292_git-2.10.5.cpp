static int list_tags(struct ref_filter *filter, struct ref_sorting *sorting, const char *format)
{
	struct ref_array array;
	char *to_free = NULL;
	int i;

	memset(&array, 0, sizeof(array));

	if (filter->lines == -1)
		filter->lines = 0;

	if (!format) {
		if (filter->lines) {
			to_free = xstrfmt("%s %%(contents:lines=%d)",
					  "%(align:15)%(refname:strip=2)%(end)",
					  filter->lines);
			format = to_free;
		} else
			format = "%(refname:strip=2)";
	}

	verify_ref_format(format);
	filter->with_commit_tag_algo = 1;
	filter_refs(&array, filter, FILTER_REFS_TAGS);
	ref_array_sort(sorting, &array);

	for (i = 0; i < array.nr; i++)
		show_ref_array_item(array.items[i], format, 0);
	ref_array_clear(&array);
	free(to_free);

	return 0;
}