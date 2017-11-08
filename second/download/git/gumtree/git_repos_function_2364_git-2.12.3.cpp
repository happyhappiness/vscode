static void handle_content_type(struct mailinfo *mi, struct strbuf *line)
{
	struct strbuf *boundary = xmalloc(sizeof(struct strbuf));
	strbuf_init(boundary, line->len);

	if (slurp_attr(line->buf, "boundary=", boundary)) {
		strbuf_insert(boundary, 0, "--", 2);
		if (++mi->content_top >= &mi->content[MAX_BOUNDARIES]) {
			error("Too many boundaries to handle");
			mi->input_error = -1;
			mi->content_top = &mi->content[MAX_BOUNDARIES] - 1;
			return;
		}
		*(mi->content_top) = boundary;
		boundary = NULL;
	}
	slurp_attr(line->buf, "charset=", &mi->charset);

	if (boundary) {
		strbuf_release(boundary);
		free(boundary);
	}
}