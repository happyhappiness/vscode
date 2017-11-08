static int copyfrom_target(struct window *ctx, const char **instructions,
			   size_t nbytes, const char *instructions_end)
{
	size_t offset;
	if (parse_int(instructions, &offset, instructions_end))
		return -1;
	if (offset >= ctx->out.len)
		return error("invalid delta: copies from the future");
	for (; nbytes > 0; nbytes--)
		strbuf_addch(&ctx->out, ctx->out.buf[offset++]);
	return 0;
}