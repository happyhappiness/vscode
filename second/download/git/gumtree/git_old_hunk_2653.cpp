	while ((commit = get_revision(opts->revs)))
		next = commit_list_append(commit, next);
}

static int create_seq_dir(void)
{
	const char *seq_dir = git_path(SEQ_DIR);

	if (file_exists(seq_dir)) {
		error(_("a cherry-pick or revert is already in progress"));
		advise(_("try \"git cherry-pick (--continue | --quit | --abort)\""));
		return -1;
	}
	else if (mkdir(seq_dir, 0777) < 0)
		die_errno(_("Could not create sequencer directory %s"), seq_dir);
	return 0;
}

static void save_head(const char *head)
{
	const char *head_file = git_path(SEQ_HEAD_FILE);
	static struct lock_file head_lock;
	struct strbuf buf = STRBUF_INIT;
	int fd;

	fd = hold_lock_file_for_update(&head_lock, head_file, LOCK_DIE_ON_ERROR);
	strbuf_addf(&buf, "%s\n", head);
	if (write_in_full(fd, buf.buf, buf.len) < 0)
		die_errno(_("Could not write to %s"), head_file);
	if (commit_lock_file(&head_lock) < 0)
		die(_("Error wrapping up %s."), head_file);
}

static int reset_for_rollback(const unsigned char *sha1)
{
	const char *argv[4];	/* reset --merge <arg> + NULL */
	argv[0] = "reset";
