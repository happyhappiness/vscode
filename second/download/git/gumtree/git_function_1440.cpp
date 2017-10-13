tatic void print_ref_list(struct ref_filter *filter, struct ref_sorting *sorting, struct ref_format *format)
{
	int i;
	struct ref_array array;
	int maxwidth = 0;
	const char *remote_prefix = "";
	struct strbuf out = STRBUF_INIT;
	char *to_free = NULL;

	/*
	 * If we are listing more than just remote branches,
	 * then remote branches will have a "remotes/" prefix.
	 * We need to account for this in the width.
	 */
	if (filter->kind != FILTER_REFS_REMOTES)
		remote_prefix = "remotes/";

	memset(&array, 0, sizeof(array));

	filter_refs(&array, filter, filter->kind | FILTER_REFS_INCLUDE_BROKEN);

	if (filter->verbose)
		maxwidth = calc_maxwidth(&array, strlen(remote_prefix));

	if (!format->format)
		format->format = to_free = build_format(filter, maxwidth, remote_prefix);
	format->use_color = branch_use_color;

	if (verify_ref_format(format))
		die(_("unable to parse format string"));

	ref_array_sort(sorting, &array);

	for (i = 0; i < array.nr; i++) {
		format_ref_array_item(array.items[i], format, &out);
		if (column_active(colopts)) {
			assert(!filter->verbose && "--column and --verbose are incompatible");
			 /* format to a string_list to let print_columns() do its job */
			string_list_append(&output, out.buf);
		} else {
			fwrite(out.buf, 1, out.len, stdout);
			putchar('\n');
		}
		strbuf_release(&out);
	}

	ref_array_clear(&array);
	free(to_free);
}