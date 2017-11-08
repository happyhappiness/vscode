static void show_stats(struct diffstat_t *data, struct diff_options *options)
{
	int i, len, add, del, adds = 0, dels = 0;
	uintmax_t max_change = 0, max_len = 0;
	int total_files = data->nr, count;
	int width, name_width, graph_width, number_width = 0, bin_width = 0;
	const char *reset, *add_c, *del_c;
	const char *line_prefix = "";
	int extra_shown = 0;

	if (data->nr == 0)
		return;

	line_prefix = diff_line_prefix(options);
	count = options->stat_count ? options->stat_count : data->nr;

	reset = diff_get_color_opt(options, DIFF_RESET);
	add_c = diff_get_color_opt(options, DIFF_FILE_NEW);
	del_c = diff_get_color_opt(options, DIFF_FILE_OLD);

	/*
	 * Find the longest filename and max number of changes
	 */
	for (i = 0; (i < count) && (i < data->nr); i++) {
		struct diffstat_file *file = data->files[i];
		uintmax_t change = file->added + file->deleted;

		if (!file->is_interesting && (change == 0)) {
			count++; /* not shown == room for one more */
			continue;
		}
		fill_print_name(file);
		len = strlen(file->print_name);
		if (max_len < len)
			max_len = len;

		if (file->is_unmerged) {
			/* "Unmerged" is 8 characters */
			bin_width = bin_width < 8 ? 8 : bin_width;
			continue;
		}
		if (file->is_binary) {
			/* "Bin XXX -> YYY bytes" */
			int w = 14 + decimal_width(file->added)
				+ decimal_width(file->deleted);
			bin_width = bin_width < w ? w : bin_width;
			/* Display change counts aligned with "Bin" */
			number_width = 3;
			continue;
		}

		if (max_change < change)
			max_change = change;
	}
	count = i; /* where we can stop scanning in data->files[] */

	/*
	 * We have width = stat_width or term_columns() columns total.
	 * We want a maximum of min(max_len, stat_name_width) for the name part.
	 * We want a maximum of min(max_change, stat_graph_width) for the +- part.
	 * We also need 1 for " " and 4 + decimal_width(max_change)
	 * for " | NNNN " and one the empty column at the end, altogether
	 * 6 + decimal_width(max_change).
	 *
	 * If there's not enough space, we will use the smaller of
	 * stat_name_width (if set) and 5/8*width for the filename,
	 * and the rest for constant elements + graph part, but no more
	 * than stat_graph_width for the graph part.
	 * (5/8 gives 50 for filename and 30 for the constant parts + graph
	 * for the standard terminal size).
	 *
	 * In other words: stat_width limits the maximum width, and
	 * stat_name_width fixes the maximum width of the filename,
	 * and is also used to divide available columns if there
	 * aren't enough.
	 *
	 * Binary files are displayed with "Bin XXX -> YYY bytes"
	 * instead of the change count and graph. This part is treated
	 * similarly to the graph part, except that it is not
	 * "scaled". If total width is too small to accommodate the
	 * guaranteed minimum width of the filename part and the
	 * separators and this message, this message will "overflow"
	 * making the line longer than the maximum width.
	 */

	if (options->stat_width == -1)
		width = term_columns() - options->output_prefix_length;
	else
		width = options->stat_width ? options->stat_width : 80;
	number_width = decimal_width(max_change) > number_width ?
		decimal_width(max_change) : number_width;

	if (options->stat_graph_width == -1)
		options->stat_graph_width = diff_stat_graph_width;

	/*
	 * Guarantee 3/8*16==6 for the graph part
	 * and 5/8*16==10 for the filename part
	 */
	if (width < 16 + 6 + number_width)
		width = 16 + 6 + number_width;

	/*
	 * First assign sizes that are wanted, ignoring available width.
	 * strlen("Bin XXX -> YYY bytes") == bin_width, and the part
	 * starting from "XXX" should fit in graph_width.
	 */
	graph_width = max_change + 4 > bin_width ? max_change : bin_width - 4;
	if (options->stat_graph_width &&
	    options->stat_graph_width < graph_width)
		graph_width = options->stat_graph_width;

	name_width = (options->stat_name_width > 0 &&
		      options->stat_name_width < max_len) ?
		options->stat_name_width : max_len;

	/*
	 * Adjust adjustable widths not to exceed maximum width
	 */
	if (name_width + number_width + 6 + graph_width > width) {
	