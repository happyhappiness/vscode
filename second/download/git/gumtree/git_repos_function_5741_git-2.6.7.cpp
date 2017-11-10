static int apply_one_window(struct line_buffer *delta, off_t *delta_len,
			    struct sliding_view *preimage, FILE *out)
{
	int rv = -1;
	struct window ctx = WINDOW_INIT(preimage);
	size_t out_len;
	size_t instructions_len;
	size_t data_len;
	assert(delta_len);

	/* "source view" offset and length already handled; */
	if (read_length(delta, &out_len, delta_len) ||
	    read_length(delta, &instructions_len, delta_len) ||
	    read_length(delta, &data_len, delta_len) ||
	    read_chunk(delta, delta_len, &ctx.instructions, instructions_len) ||
	    read_chunk(delta, delta_len, &ctx.data, data_len))
		goto error_out;
	strbuf_grow(&ctx.out, out_len);
	if (apply_window_in_core(&ctx))
		goto error_out;
	if (ctx.out.len != out_len) {
		rv = error("invalid delta: incorrect postimage length");
		goto error_out;
	}
	if (write_strbuf(&ctx.out, out))
		goto error_out;
	rv = 0;
error_out:
	window_release(&ctx);
	return rv;
}