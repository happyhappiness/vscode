const char *setup_temporary_shallow(const struct sha1_array *extra)
{
	struct strbuf sb = STRBUF_INIT;
	int fd;

	if (write_shallow_commits(&sb, 0, extra)) {
		fd = xmks_tempfile(&temporary_shallow, git_path("shallow_XXXXXX"));

		if (write_in_full(fd, sb.buf, sb.len) != sb.len)
			die_errno("failed to write to %s",
				  get_tempfile_path(&temporary_shallow));
		close_tempfile(&temporary_shallow);
		strbuf_release(&sb);
		return get_tempfile_path(&temporary_shallow);
	}
	/*
	 * is_repository_shallow() sees empty string as "no shallow
	 * file".
	 */
	return get_tempfile_path(&temporary_shallow);
}