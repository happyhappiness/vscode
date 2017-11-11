static int execute_one_instruction(struct window *ctx,
				const char **instructions, size_t *data_pos)
{
	unsigned int instruction;
	const char *insns_end = ctx->instructions.buf + ctx->instructions.len;
	size_t nbytes;
	assert(ctx);
	assert(instructions && *instructions);
	assert(data_pos);

	instruction = (unsigned char) **instructions;
	if (parse_first_operand(instructions, &nbytes, insns_end))
		return -1;
	switch (instruction & INSN_MASK) {
	case INSN_COPYFROM_SOURCE:
		return copyfrom_source(ctx, instructions, nbytes, insns_end);
	case INSN_COPYFROM_TARGET:
		return copyfrom_target(ctx, instructions, nbytes, insns_end);
	case INSN_COPYFROM_DATA:
		return copyfrom_data(ctx, data_pos, nbytes);
	default:
		return error("invalid delta: unrecognized instruction");
	}
}