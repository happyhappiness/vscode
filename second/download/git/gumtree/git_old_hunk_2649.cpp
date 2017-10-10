static void free_message(struct commit *commit, struct commit_message *msg)
{
	free(msg->parent_label);
	unuse_commit_buffer(commit, msg->message);
}

static void write_cherry_pick_head(struct commit *commit, const char *pseudoref)
{
	const char *filename;
	int fd;
	struct strbuf buf = STRBUF_INIT;

	strbuf_addf(&buf, "%s\n", sha1_to_hex(commit->object.sha1));

	filename = git_path("%s", pseudoref);
	fd = open(filename, O_WRONLY | O_CREAT, 0666);
	if (fd < 0)
		die_errno(_("Could not open '%s' for writing"), filename);
	if (write_in_full(fd, buf.buf, buf.len) != buf.len || close(fd))
		die_errno(_("Could not write to '%s'"), filename);
	strbuf_release(&buf);
}

static void print_advice(int show_hint, struct replay_opts *opts)
{
	char *msg = getenv("GIT_CHERRY_PICK_HELP");

	if (msg) {
		fprintf(stderr, "%s\n", msg);
		/*
		 * A conflict has occurred but the porcelain
		 * (typically rebase --interactive) wants to take care
		 * of the commit itself so remove CHERRY_PICK_HEAD
		 */
		unlink(git_path("CHERRY_PICK_HEAD"));
		return;
	}

	if (show_hint) {
		if (opts->no_commit)
			advise(_("after resolving the conflicts, mark the corrected paths\n"
