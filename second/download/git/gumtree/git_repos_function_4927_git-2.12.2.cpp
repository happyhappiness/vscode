static void use(int bytes)
{
	if (bytes > len)
		die("used more bytes than were available");
	len -= bytes;
	offset += bytes;

	/* make sure off_t is sufficiently large not to wrap */
	if (signed_add_overflows(consumed_bytes, bytes))
		die("pack too large for current definition of off_t");
	consumed_bytes += bytes;
	if (max_input_size && consumed_bytes > max_input_size)
		die(_("pack exceeds maximum allowed size"));
}