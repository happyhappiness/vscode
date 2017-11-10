static void reset_dump_ctx(const char *url)
{
	strbuf_reset(&dump_ctx.url);
	if (url)
		strbuf_addstr(&dump_ctx.url, url);
	dump_ctx.version = 1;
	strbuf_reset(&dump_ctx.uuid);
}