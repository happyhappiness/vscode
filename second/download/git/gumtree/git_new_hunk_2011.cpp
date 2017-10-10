		die(_("%s: Unable to write new index file"), action_name(opts));
	rollback_lock_file(&index_lock);

	if (opts->signoff)
		append_signoff(msgbuf, 0, 0);

	if (!clean)
		append_conflicts_hint(msgbuf);

	return !clean;
}

static int is_index_unchanged(void)
{
