void quote_two_c_style(struct strbuf *sb, const char *prefix, const char *path, int nodq)
{
	if (quote_c_style(prefix, NULL, NULL, 0) ||
	    quote_c_style(path, NULL, NULL, 0)) {
		if (!nodq)
			strbuf_addch(sb, '"');
		quote_c_style(prefix, sb, NULL, 1);
		quote_c_style(path, sb, NULL, 1);
		if (!nodq)
			strbuf_addch(sb, '"');
	} else {
		strbuf_addstr(sb, prefix);
		strbuf_addstr(sb, path);
	}
}