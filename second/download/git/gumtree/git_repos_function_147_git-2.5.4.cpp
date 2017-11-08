static void check_non_tip(void)
{
	static const char *argv[] = {
		"rev-list", "--stdin", NULL,
	};
	static struct child_process cmd = CHILD_PROCESS_INIT;
	struct object *o;
	char namebuf[42]; /* ^ + SHA-1 + LF */
	int i;

	/*
	 * In the normal in-process case without
	 * uploadpack.allowReachableSHA1InWant,
	 * non-tip requests can never happen.
	 */
	if (!stateless_rpc && !(allow_unadvertised_object_request & ALLOW_REACHABLE_SHA1))
		goto error;

	cmd.argv = argv;
	cmd.git_cmd = 1;
	cmd.no_stderr = 1;
	cmd.in = -1;
	cmd.out = -1;

	if (start_command(&cmd))
		goto error;

	/*
	 * If rev-list --stdin encounters an unknown commit, it
	 * terminates, which will cause SIGPIPE in the write loop
	 * below.
	 */
	sigchain_push(SIGPIPE, SIG_IGN);

	namebuf[0] = '^';
	namebuf[41] = '\n';
	for (i = get_max_object_index(); 0 < i; ) {
		o = get_indexed_object(--i);
		if (!o)
			continue;
		if (!is_our_ref(o))
			continue;
		memcpy(namebuf + 1, sha1_to_hex(o->sha1), 40);
		if (write_in_full(cmd.in, namebuf, 42) < 0)
			goto error;
	}
	namebuf[40] = '\n';
	for (i = 0; i < want_obj.nr; i++) {
		o = want_obj.objects[i].item;
		if (is_our_ref(o))
			continue;
		memcpy(namebuf, sha1_to_hex(o->sha1), 40);
		if (write_in_full(cmd.in, namebuf, 41) < 0)
			goto error;
	}
	close(cmd.in);

	sigchain_pop(SIGPIPE);

	/*
	 * The commits out of the rev-list are not ancestors of
	 * our ref.
	 */
	i = read_in_full(cmd.out, namebuf, 1);
	if (i)
		goto error;
	close(cmd.out);

	/*
	 * rev-list may have died by encountering a bad commit
	 * in the history, in which case we do want to bail out
	 * even when it showed no commit.
	 */
	if (finish_command(&cmd))
		goto error;

	/* All the non-tip ones are ancestors of what we advertised */
	return;

error:
	/* Pick one of them (we know there at least is one) */
	for (i = 0; i < want_obj.nr; i++) {
		o = want_obj.objects[i].item;
		if (!is_our_ref(o))
			die("git upload-pack: not our ref %s",
			    sha1_to_hex(o->sha1));
	}
}