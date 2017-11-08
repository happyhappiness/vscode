static int copyfrom_source(struct window *ctx, const char **instructions,
			   size_t nbytes, const char *insns_end)
{
	size_t offset;
	if (parse_int(instructions, &offset, insns_end))
		return -1;
	if (unsigned_add_overflows(offset, nbytes) ||
	    offset + nbytes > ctx->in->width)
		return error("invalid delta: copies source data outside view");
	strbuf_add(&ctx->out, ctx->in->buf.buf + offset, nbytes);
	return 0;
}