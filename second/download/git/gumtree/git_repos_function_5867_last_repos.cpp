static void fmt_tag_signature(struct strbuf *tagbuf,
			      struct strbuf *sig,
			      const char *buf,
			      unsigned long len)
{
	const char *tag_body = strstr(buf, "\n\n");
	if (tag_body) {
		tag_body += 2;
		strbuf_add(tagbuf, tag_body, buf + len - tag_body);
	}
	strbuf_complete_line(tagbuf);
	if (sig->len) {
		strbuf_addch(tagbuf, '\n');
		strbuf_add_commented_lines(tagbuf, sig->buf, sig->len);
	}
}