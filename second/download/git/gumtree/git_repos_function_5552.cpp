static void restore_state(const unsigned char *head,
			  const unsigned char *stash)
{
	struct strbuf sb = STRBUF_INIT;
	const char *args[] = { "stash", "apply", NULL, NULL };

	if (is_null_sha1(stash))
		return;

	reset_hard(head, 1);

	args[2] = sha1_to_hex(stash);

	/*
	 * It is OK to ignore error here, for example when there was
	 * nothing to restore.
	 */
	run_command_v_opt(args, RUN_GIT_CMD);

	strbuf_release(&sb);
	refresh_cache(REFRESH_QUIET);
}