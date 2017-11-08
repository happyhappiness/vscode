static void reset_node_ctx(char *fname)
{
	node_ctx.type = 0;
	node_ctx.action = NODEACT_UNKNOWN;
	node_ctx.prop_length = -1;
	node_ctx.text_length = -1;
	strbuf_reset(&node_ctx.src);
	node_ctx.srcRev = 0;
	strbuf_reset(&node_ctx.dst);
	if (fname)
		strbuf_addstr(&node_ctx.dst, fname);
	node_ctx.text_delta = 0;
	node_ctx.prop_delta = 0;
}