const char *setup_temporary_shallow(const struct sha1_array *extra)
{
	struct strbuf sb = STRBUF_INIT;
	int fd;

	if (temporary_shallow.len)
		die("BUG: attempt to create two temporary shallow files");

	if (write_shallow_commits(&sb, 0, extra)) {
		strbuf_addstr(&temporary_shallow, git_path("shallow_XXXXXX"));
		fd = xmkstemp(temporary_shallow.buf);

		atexit(remove_temporary_shallow);
		sigchain_push_common(remove_temporary_shallow_on_signal);

		if (write_in_full(fd, sb.buf, sb.len) != sb.len)
			die_errno("failed to write to %s",
				  temporary_shallow.buf);
		close(fd);
		strbuf_release(&sb);
		return temporary_shallow.buf;
	}
	/*
	 * is_repository_shallow() sees empty string as "no shallow
	 * file".
	 */
	return temporary_shallow.buf;
}