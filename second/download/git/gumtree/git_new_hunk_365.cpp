	input_offset += bytes;

	/* make sure off_t is sufficiently large not to wrap */
	if (signed_add_overflows(consumed_bytes, bytes))
		die(_("pack too large for current definition of off_t"));
	consumed_bytes += bytes;
	if (max_input_size && consumed_bytes > max_input_size)
		die(_("pack exceeds maximum allowed size"));
}

static const char *open_pack_file(const char *pack_name)
{
	if (from_stdin) {
		input_fd = 0;
