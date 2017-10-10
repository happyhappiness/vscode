
	filter_refs(&array, filter, filter->kind | FILTER_REFS_INCLUDE_BROKEN);

	if (filter->verbose)
		maxwidth = calc_maxwidth(&array, strlen(remote_prefix));

	if (!format)
		format = to_free = build_format(filter, maxwidth, remote_prefix);
	verify_ref_format(format);

	ref_array_sort(sorting, &array);

	for (i = 0; i < array.nr; i++) {
		format_ref_array_item(array.items[i], format, 0, &out);
		if (column_active(colopts)) {
			assert(!filter->verbose && "--column and --verbose are incompatible");
			 /* format to a string_list to let print_columns() do its job */
			string_list_append(&output, out.buf);
		} else {
			fwrite(out.buf, 1, out.len, stdout);
