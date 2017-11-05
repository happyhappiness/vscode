static void strbuf_add_indented_text(struct strbuf *buf, const char *text,
				     int indent, int indent2)
{
	if (indent < 0)
		indent = 0;
	while (*text) {
		const char *eol = strchrnul(text, '\n');
		if (*eol == '\n')
			eol++;
		strbuf_addchars(buf, ' ', indent);
		strbuf_add(buf, text, eol - text);
		text = eol;
		indent = indent2;
	}
}