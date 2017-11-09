static int display_cell(struct column_data *data, int initial_width,
			const char *empty_cell, int x, int y)
{
	int i, len, newline;

	i = XY2LINEAR(data, x, y);
	if (i >= data->list->nr)
		return -1;

	len = data->len[i];
	if (data->width && data->len[data->width[x]] < initial_width) {
		/*
		 * empty_cell has initial_width chars, if real column
		 * is narrower, increase len a bit so we fill less
		 * space.
		 */
		len += initial_width - data->len[data->width[x]];
		len -= data->opts.padding;
	}

	if (COL_LAYOUT(data->colopts) == COL_COLUMN)
		newline = i + data->rows >= data->list->nr;
	else
		newline = x == data->cols - 1 || i == data->list->nr - 1;

	printf("%s%s%s",
	       x == 0 ? data->opts.indent : "",
	       data->list->items[i].string,
	       newline ? data->opts.nl : empty_cell + len);
	return 0;
}