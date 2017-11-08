static void emit_rewrite_diff(const char *name_a,
			      const char *name_b,
			      struct diff_filespec *one,
			      struct diff_filespec *two,
			      struct userdiff_driver *textconv_one,
			      struct userdiff_driver *textconv_two,
			      struct diff_options *o)
{
	int lc_a, lc_b;
	const char *name_a_tab, *name_b_tab;
	const char *metainfo = diff_get_color(o->use_color, DIFF_METAINFO);
	const char *fraginfo = diff_get_color(o->use_color, DIFF_FRAGINFO);
	const char *reset = diff_get_color(o->use_color, DIFF_RESET);
	static struct strbuf a_name = STRBUF_INIT, b_name = STRBUF_INIT;
	const char *a_prefix, *b_prefix;
	char *data_one, *data_two;
	size_t size_one, size_two;
	struct emit_callback ecbdata;
	const char *line_prefix = diff_line_prefix(o);

	if (diff_mnemonic_prefix && DIFF_OPT_TST(o, REVERSE_DIFF)) {
		a_prefix = o->b_prefix;
		b_prefix = o->a_prefix;
	} else {
		a_prefix = o->a_prefix;
		b_prefix = o->b_prefix;
	}

	name_a += (*name_a == '/');
	name_b += (*name_b == '/');
	name_a_tab = strchr(name_a, ' ') ? "\t" : "";
	name_b_tab = strchr(name_b, ' ') ? "\t" : "";

	strbuf_reset(&a_name);
	strbuf_reset(&b_name);
	quote_two_c_style(&a_name, a_prefix, name_a, 0);
	quote_two_c_style(&b_name, b_prefix, name_b, 0);

	size_one = fill_textconv(textconv_one, one, &data_one);
	size_two = fill_textconv(textconv_two, two, &data_two);

	memset(&ecbdata, 0, sizeof(ecbdata));
	ecbdata.color_diff = want_color(o->use_color);
	ecbdata.ws_rule = whitespace_rule(name_b);
	ecbdata.opt = o;
	if (ecbdata.ws_rule & WS_BLANK_AT_EOF) {
		mmfile_t mf1, mf2;
		mf1.ptr = (char *)data_one;
		mf2.ptr = (char *)data_two;
		mf1.size = size_one;
		mf2.size = size_two;
		check_blank_at_eof(&mf1, &mf2, &ecbdata);
	}
	ecbdata.lno_in_preimage = 1;
	ecbdata.lno_in_postimage = 1;

	lc_a = count_lines(data_one, size_one);
	lc_b = count_lines(data_two, size_two);
	fprintf(o->file,
		"%s%s--- %s%s%s\n%s%s+++ %s%s%s\n%s%s@@ -",
		line_prefix, metainfo, a_name.buf, name_a_tab, reset,
		line_prefix, metainfo, b_name.buf, name_b_tab, reset,
		line_prefix, fraginfo);
	if (!o->irreversible_delete)
		print_line_count(o->file, lc_a);
	else
		fprintf(o->file, "?,?");
	fprintf(o->file, " +");
	print_line_count(o->file, lc_b);
	fprintf(o->file, " @@%s\n", reset);
	if (lc_a && !o->irreversible_delete)
		emit_rewrite_lines(&ecbdata, '-', data_one, size_one);
	if (lc_b)
		emit_rewrite_lines(&ecbdata, '+', data_two, size_two);
	if (textconv_one)
		free((char *)data_one);
	if (textconv_two)
		free((char *)data_two);
}