static inline int cmp_header(const struct strbuf *line, const char *hdr)
{
	int len = strlen(hdr);
	return !strncasecmp(line->buf, hdr, len) && line->len > len &&
			line->buf[len] == ':' && isspace(line->buf[len + 1]);
}