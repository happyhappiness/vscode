static int item_length(unsigned int colopts, const char *s)
{
	int len, i = 0;
	struct strbuf str = STRBUF_INIT;

	strbuf_addstr(&str, s);
	while ((s = strstr(str.buf + i, "\033[")) != NULL) {
		int len = strspn(s + 2, "0123456789;");
		i = s - str.buf;
		strbuf_remove(&str, i, len + 3); /* \033[<len><func char> */
	}
	len = utf8_strwidth(str.buf);
	strbuf_release(&str);
	return len;
}