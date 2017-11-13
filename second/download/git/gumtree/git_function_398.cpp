static void use(int bytes)
{
	if (bytes > input_len)
		die(_("used more bytes than were available"));
	input_crc32 = crc32(input_crc32, input_buffer + input_offset, bytes);
	input_len -= bytes;
	input_offset += bytes;

	/* make sure off_t is sufficiently large not to wrap */
	if (signed_add_overflows(consumed_bytes, bytes))
		die(_("pack too large for current definition of off_t"));
	consumed_bytes += bytes;
	if (max_input_size && consumed_bytes > max_input_size)
		die(_("pack exceeds maximum allowed size"));
}