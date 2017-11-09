static void shrink_columns(struct column_data *data)
{
	REALLOC_ARRAY(data->width, data->cols);
	while (data->rows > 1) {
		int x, total_width, cols, rows;
		rows = data->rows;
		cols = data->cols;

		data->rows--;
		data->cols = DIV_ROUND_UP(data->list->nr, data->rows);
		if (data->cols != cols)
			REALLOC_ARRAY(data->width, data->cols);
		compute_column_width(data);

		total_width = strlen(data->opts.indent);
		for (x = 0; x < data->cols; x++) {
			total_width += data->len[data->width[x]];
			total_width += data->opts.padding;
		}
		if (total_width > data->opts.width) {
			data->rows = rows;
			data->cols = cols;
			break;
		}
	}
	compute_column_width(data);
}