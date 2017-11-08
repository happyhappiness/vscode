void svndump_reset(void)
{
	strbuf_release(&dump_ctx.uuid);
	strbuf_release(&dump_ctx.url);
	strbuf_release(&rev_ctx.log);
	strbuf_release(&rev_ctx.author);
}