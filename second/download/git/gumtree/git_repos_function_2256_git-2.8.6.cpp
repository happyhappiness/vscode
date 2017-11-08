void strbuf_addstr_xml_quoted(struct strbuf *buf, const char *s)
{
	while (*s) {
		size_t len = strcspn(s, "\"<>&");
		strbuf_add(buf, s, len);
		s += len;
		switch (*s) {
		case '"':
			strbuf_addstr(buf, "&quot;");
			break;
		case '<':
			strbuf_addstr(buf, "&lt;");
			break;
		case '>':
			strbuf_addstr(buf, "&gt;");
			break;
		case '&':
			strbuf_addstr(buf, "&amp;");
			break;
		case 0:
			return;
		}
		s++;
	}
}