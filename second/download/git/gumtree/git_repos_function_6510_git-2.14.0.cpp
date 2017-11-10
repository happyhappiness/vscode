static int copyfrom_data(struct window *ctx, size_t *data_pos, size_t nbytes)
{
	const size_t pos = *data_pos;
	if (unsigned_add_overflows(pos, nbytes) ||
	    pos + nbytes > ctx->data.len)
		return error("invalid delta: copies unavailable inline data");
	strbuf_add(&ctx->out, ctx->data.buf + pos, nbytes);
	*data_pos += nbytes;
	return 0;
}