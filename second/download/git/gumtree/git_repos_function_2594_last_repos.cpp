static int find_boundary(struct mailinfo *mi, struct strbuf *line)
{
	while (!strbuf_getline_lf(line, mi->input)) {
		if (*(mi->content_top) && is_multipart_boundary(mi, line))
			return 1;
	}
	return 0;
}