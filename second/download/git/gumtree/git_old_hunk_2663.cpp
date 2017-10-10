int write_shallow_commits(struct strbuf *out, int use_pack_protocol,
			  const struct sha1_array *extra)
{
	return write_shallow_commits_1(out, use_pack_protocol, extra, 0);
}

static struct strbuf temporary_shallow = STRBUF_INIT;

static void remove_temporary_shallow(void)
{
	if (temporary_shallow.len) {
		unlink_or_warn(temporary_shallow.buf);
		strbuf_reset(&temporary_shallow);
	}
}

static void remove_temporary_shallow_on_signal(int signo)
{
	remove_temporary_shallow();
	sigchain_pop(signo);
	raise(signo);
}

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

void setup_alternate_shallow(struct lock_file *shallow_lock,
			     const char **alternate_shallow_file,
			     const struct sha1_array *extra)
{
	struct strbuf sb = STRBUF_INIT;
	int fd;

	fd = hold_lock_file_for_update(shallow_lock, git_path("shallow"),
				       LOCK_DIE_ON_ERROR);
	check_shallow_file_for_update();
	if (write_shallow_commits(&sb, 0, extra)) {
		if (write_in_full(fd, sb.buf, sb.len) != sb.len)
			die_errno("failed to write to %s",
				  shallow_lock->filename.buf);
		*alternate_shallow_file = shallow_lock->filename.buf;
	} else
		/*
		 * is_repository_shallow() sees empty string as "no
		 * shallow file".
		 */
		*alternate_shallow_file = "";
