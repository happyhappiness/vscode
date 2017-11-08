static int is_multipart_boundary(const struct strbuf *line)
{
	return (((*content_top)->len <= line->len) &&
		!memcmp(line->buf, (*content_top)->buf, (*content_top)->len));
}