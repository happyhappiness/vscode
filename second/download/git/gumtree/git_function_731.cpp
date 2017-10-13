static void wt_porcelain_v2_print_other(
	struct string_list_item *it,
	struct wt_status *s,
	char prefix)
{
	struct strbuf buf = STRBUF_INIT;
	const char *path;
	char eol_char;

	if (s->null_termination) {
		path = it->string;
		eol_char = '\0';
	} else {
		path = quote_path(it->string, s->prefix, &buf);
		eol_char = '\n';
	}

	fprintf(s->fp, "%c %s%c", prefix, path, eol_char);

	strbuf_release(&buf);
}