void fast_export_buf_to_data(const struct strbuf *data)
{
	printf("data %"PRIuMAX"\n", (uintmax_t)data->len);
	fwrite(data->buf, data->len, 1, stdout);
	fputc('\n', stdout);
}