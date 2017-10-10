	const char *meta = diff_get_color(ecbdata->color_diff, DIFF_METAINFO);
	const char *context = diff_get_color(ecbdata->color_diff, DIFF_CONTEXT);
	const char *reset = diff_get_color(ecbdata->color_diff, DIFF_RESET);
	struct diff_options *o = ecbdata->opt;
	const char *line_prefix = diff_line_prefix(o);

	if (ecbdata->header) {
		fprintf(ecbdata->opt->file, "%s", ecbdata->header->buf);
		strbuf_reset(ecbdata->header);
		ecbdata->header = NULL;
	}
	*(ecbdata->found_changesp) = 1;

	if (ecbdata->label_path[0]) {
		const char *name_a_tab, *name_b_tab;

		name_a_tab = strchr(ecbdata->label_path[0], ' ') ? "\t" : "";
		name_b_tab = strchr(ecbdata->label_path[1], ' ') ? "\t" : "";

		fprintf(ecbdata->opt->file, "%s%s--- %s%s%s\n",
			line_prefix, meta, ecbdata->label_path[0], reset, name_a_tab);
		fprintf(ecbdata->opt->file, "%s%s+++ %s%s%s\n",
			line_prefix, meta, ecbdata->label_path[1], reset, name_b_tab);
		ecbdata->label_path[0] = ecbdata->label_path[1] = NULL;
	}

	if (diff_suppress_blank_empty
	    && len == 2 && line[0] == ' ' && line[1] == '\n') {
