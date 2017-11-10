static void remove_temporary_shallow(void)
{
	if (temporary_shallow.len) {
		unlink_or_warn(temporary_shallow.buf);
		strbuf_reset(&temporary_shallow);
	}
}