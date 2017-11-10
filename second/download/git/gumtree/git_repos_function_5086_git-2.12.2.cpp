static void write_name(const char *name)
{
	/*
	 * Prepend the super_prefix to name to construct the full_name to be
	 * written.
	 */
	struct strbuf full_name = STRBUF_INIT;
	if (super_prefix) {
		strbuf_addstr(&full_name, super_prefix);
		strbuf_addstr(&full_name, name);
		name = full_name.buf;
	}

	/*
	 * With "--full-name", prefix_len=0; this caller needs to pass
	 * an empty string in that case (a NULL is good for "").
	 */
	write_name_quoted_relative(name, prefix_len ? prefix : NULL,
				   stdout, line_terminator);

	strbuf_release(&full_name);
}