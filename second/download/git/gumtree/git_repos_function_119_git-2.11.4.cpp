void userformat_find_requirements(const char *fmt, struct userformat_want *w)
{
	struct strbuf dummy = STRBUF_INIT;

	if (!fmt) {
		if (!user_format)
			return;
		fmt = user_format;
	}
	strbuf_expand(&dummy, fmt, userformat_want_item, w);
	strbuf_release(&dummy);
}