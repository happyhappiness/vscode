}

static void fn_out_consume(void *priv, char *line, unsigned long len)
{
	struct emit_callback *ecbdata = priv;
	const char *meta = diff_get_color(ecbdata->color_diff, DIFF_METAINFO);
	const char *plain = diff_get_color(ecbdata->color_diff, DIFF_PLAIN);
	const char *reset = diff_get_color(ecbdata->color_diff, DIFF_RESET);
	struct diff_options *o = ecbdata->opt;
	const char *line_prefix = diff_line_prefix(o);

	if (ecbdata->header) {
		fprintf(ecbdata->opt->file, "%s", ecbdata->header->buf);
