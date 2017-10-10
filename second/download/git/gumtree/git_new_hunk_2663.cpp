int write_shallow_commits(struct strbuf *out, int use_pack_protocol,
			  const struct sha1_array *extra)
{
	return write_shallow_commits_1(out, use_pack_protocol, extra, 0);
}

static struct tempfile temporary_shallow;

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

void setup_alternate_shallow(struct lock_file *shallow_lock,
			     const char **alternate_shallow_file,
			     const struct sha1_array *extra)
{
	struct strbuf sb = STRBUF_INIT;
	int fd;

	fd = hold_lock_file_for_update(shallow_lock, git_path_shallow(),
				       LOCK_DIE_ON_ERROR);
	check_shallow_file_for_update();
	if (write_shallow_commits(&sb, 0, extra)) {
		if (write_in_full(fd, sb.buf, sb.len) != sb.len)
			die_errno("failed to write to %s",
				  get_lock_file_path(shallow_lock));
		*alternate_shallow_file = get_lock_file_path(shallow_lock);
	} else
		/*
		 * is_repository_shallow() sees empty string as "no
		 * shallow file".
		 */
		*alternate_shallow_file = "";
