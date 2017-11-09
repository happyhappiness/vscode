void svndump_deinit(void)
{
	fast_export_deinit();
	reset_dump_ctx(NULL);
	reset_rev_ctx(0);
	reset_node_ctx(NULL);
	strbuf_release(&rev_ctx.log);
	strbuf_release(&rev_ctx.author);
	strbuf_release(&rev_ctx.note);
	strbuf_release(&node_ctx.src);
	strbuf_release(&node_ctx.dst);
	if (buffer_deinit(&input))
		fprintf(stderr, "Input error\n");
	if (ferror(stdout))
		fprintf(stderr, "Output error\n");
}