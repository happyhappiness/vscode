static void display_table(const struct string_list *list,
			  unsigned int colopts,
			  const struct column_options *opts)
{
	struct column_data data;
	int x, y, i, initial_width;
	char *empty_cell;

	memset(&data, 0, sizeof(data));
	data.list = list;
	data.colopts = colopts;
	data.opts = *opts;

	ALLOC_ARRAY(data.len, list->nr);
	for (i = 0; i < list->nr; i++)
		data.len[i] = item_length(colopts, list->items[i].string);

	layout(&data, &initial_width);

	if (colopts & COL_DENSE)
		shrink_columns(&data);

	empty_cell = xmallocz(initial_width);
	memset(empty_cell, ' ', initial_width);
	for (y = 0; y < data.rows; y++) {
		for (x = 0; x < data.cols; x++)
			if (display_cell(&data, initial_width, empty_cell, x, y))
				break;
	}

	free(data.len);
	free(data.width);
	free(empty_cell);
}