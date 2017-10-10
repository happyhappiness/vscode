}

static int rollback_single_pick(void)
{
	unsigned char head_sha1[20];

	if (!file_exists(git_path_cherry_pick_head()) &&
	    !file_exists(git_path_revert_head()))
		return error(_("no cherry-pick or revert in progress"));
	if (read_ref_full("HEAD", 0, head_sha1, NULL))
		return error(_("cannot resolve HEAD"));
	if (is_null_sha1(head_sha1))
		return error(_("cannot abort from a branch yet to be born"));
	return reset_for_rollback(head_sha1);
}

static int sequencer_rollback(struct replay_opts *opts)
{
	FILE *f;
	unsigned char sha1[20];
	struct strbuf buf = STRBUF_INIT;

	f = fopen(git_path_head_file(), "r");
	if (!f && errno == ENOENT) {
		/*
		 * There is no multiple-cherry-pick in progress.
		 * If CHERRY_PICK_HEAD or REVERT_HEAD indicates
		 * a single-cherry-pick in progress, abort that.
		 */
		return rollback_single_pick();
	}
	if (!f)
		return error(_("cannot open %s: %s"), git_path_head_file(),
						strerror(errno));
	if (strbuf_getline(&buf, f, '\n')) {
		error(_("cannot read %s: %s"), git_path_head_file(),
		      ferror(f) ?  strerror(errno) : _("unexpected end of file"));
		fclose(f);
		goto fail;
	}
	fclose(f);
	if (get_sha1_hex(buf.buf, sha1) || buf.buf[40] != '\0') {
		error(_("stored pre-cherry-pick HEAD file '%s' is corrupt"),
			git_path_head_file());
		goto fail;
	}
	if (reset_for_rollback(sha1))
		goto fail;
	remove_sequencer_state();
	strbuf_release(&buf);
