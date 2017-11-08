static void print_ref_list(struct ref_filter *filter, struct ref_sorting *sorting)
{
	int i;
	struct ref_array array;
	int maxwidth = 0;
	const char *remote_prefix = "";

	/*
	 * If we are listing more than just remote branches,
	 * then remote branches will have a "remotes/" prefix.
	 * We need to account for this in the width.
	 */
	if (filter->kind != FILTER_REFS_REMOTES)
		remote_prefix = "remotes/";

	memset(&array, 0, sizeof(array));

	verify_ref_format("%(refname)%(symref)");
	filter_refs(&array, filter, filter->kind | FILTER_REFS_INCLUDE_BROKEN);

	if (filter->verbose)
		maxwidth = calc_maxwidth(&array, strlen(remote_prefix));

	ref_array_sort(sorting, &array);

	for (i = 0; i < array.nr; i++)
		format_and_print_ref_item(array.items[i], maxwidth, filter, remote_prefix);

	ref_array_clear(&array);
}