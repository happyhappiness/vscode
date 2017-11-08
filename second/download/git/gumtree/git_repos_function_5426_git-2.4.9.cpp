static int apply_window_in_core(struct window *ctx)
{
	const char *instructions;
	size_t data_pos = 0;

	/*
	 * Fill ctx->out.buf using data from the source, target,
	 * and inline data views.
	 */
	for (instructions = ctx->instructions.buf;
	     instructions != ctx->instructions.buf + ctx->instructions.len;
	     )
		if (execute_one_instruction(ctx, &instructions, &data_pos))
			return -1;
	if (data_pos != ctx->data.len)
		return error("invalid delta: does not copy all inline data");
	return 0;
}