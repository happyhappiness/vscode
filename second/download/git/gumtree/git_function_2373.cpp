static void handle_content_type(struct strbuf *line)
{
	struct strbuf *boundary = xmalloc(sizeof(struct strbuf));
	strbuf_init(boundary, line->len);

	if (slurp_attr(line->buf, "boundary=", boundary)) {
		strbuf_insert(boundary, 0, "--", 2);
		if (++content_top > &content[MAX_BOUNDARIES]) {
			fprintf(stderr, "Too many boundaries to handle\n");
			exit(1);
		}
		*content_top = boundary;
		boundary = NULL;
	}
	slurp_attr(line->buf, "charset=", &charset);

	if (boundary) {
		strbuf_release(boundary);
		free(boundary);
	}
}