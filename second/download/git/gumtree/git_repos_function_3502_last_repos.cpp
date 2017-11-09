static void compute_column_width(struct column_data *data)
{
	int i, x, y;
	for (x = 0; x < data->cols; x++) {
		data->width[x] = XY2LINEAR(data, x, 0);
		for (y = 0; y < data->rows; y++) {
			i = XY2LINEAR(data, x, y);
			if (i < data->list->nr &&
			    data->len[data->width[x]] < data->len[i])
				data->width[x] = i;
		}
	}
}