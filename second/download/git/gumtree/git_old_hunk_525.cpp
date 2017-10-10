			advise(_("after resolving the conflicts, mark the corrected paths\n"
				 "with 'git add <paths>' or 'git rm <paths>'\n"
				 "and commit the result with 'git commit'"));
	}
}

static void write_message(struct strbuf *msgbuf, const char *filename)
{
	static struct lock_file msg_file;

	int msg_fd = hold_lock_file_for_update(&msg_file, filename,
					       LOCK_DIE_ON_ERROR);
	if (write_in_full(msg_fd, msgbuf->buf, msgbuf->len) < 0)
		die_errno(_("Could not write to %s"), filename);
	strbuf_release(msgbuf);
	if (commit_lock_file(&msg_file) < 0)
		die(_("Error wrapping up %s."), filename);
}

static struct tree *empty_tree(void)
{
	return lookup_tree(EMPTY_TREE_SHA1_BIN);
}

static int error_dirty_index(struct replay_opts *opts)
{
	if (read_cache_unmerged())
		return error_resolve_conflict(action_name(opts));

	/* Different translation strings for cherry-pick and revert */
	if (opts->action == REPLAY_PICK)
		error(_("Your local changes would be overwritten by cherry-pick."));
	else
		error(_("Your local changes would be overwritten by revert."));

	if (advice_commit_before_merge)
		advise(_("Commit your changes or stash them to proceed."));
	return -1;
}

static int fast_forward_to(const unsigned char *to, const unsigned char *from,
			int unborn, struct replay_opts *opts)
{
	struct ref_transaction *transaction;
	struct strbuf sb = STRBUF_INIT;
	struct strbuf err = STRBUF_INIT;

	read_cache();
	if (checkout_fast_forward(from, to, 1))
		exit(128); /* the callee should have complained already */

	strbuf_addf(&sb, _("%s: fast-forward"), action_name(opts));

	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_update(transaction, "HEAD",
				   to, unborn ? null_sha1 : from,
				   0, sb.buf, &err) ||
