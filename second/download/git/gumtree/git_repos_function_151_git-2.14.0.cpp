static int do_reachable_revlist(struct child_process *cmd,
				struct object_array *src,
				struct object_array *reachable)
{
	static const char *argv[] = {
		"rev-list", "--stdin", NULL,
	};
	struct object *o;
	char namebuf[42]; /* ^ + SHA-1 + LF */
	int i;

	cmd->argv = argv;
	cmd->git_cmd = 1;
	cmd->no_stderr = 1;
	cmd->in = -1;
	cmd->out = -1;

	/*
	 * If the next rev-list --stdin encounters an unknown commit,
	 * it terminates, which will cause SIGPIPE in the write loop
	 * below.
	 */
	sigchain_push(SIGPIPE, SIG_IGN);

	if (start_command(cmd))
		goto error;

	namebuf[0] = '^';
	namebuf[GIT_SHA1_HEXSZ + 1] = '\n';
	for (i = get_max_object_index(); 0 < i; ) {
		o = get_indexed_object(--i);
		if (!o)
			continue;
		if (reachable && o->type == OBJ_COMMIT)
			o->flags &= ~TMP_MARK;
		if (!is_our_ref(o))
			continue;
		memcpy(namebuf + 1, oid_to_hex(&o->oid), GIT_SHA1_HEXSZ);
		if (write_in_full(cmd->in, namebuf, GIT_SHA1_HEXSZ + 2) < 0)
			goto error;
	}
	namebuf[GIT_SHA1_HEXSZ] = '\n';
	for (i = 0; i < src->nr; i++) {
		o = src->objects[i].item;
		if (is_our_ref(o)) {
			if (reachable)
				add_object_array(o, NULL, reachable);
			continue;
		}
		if (reachable && o->type == OBJ_COMMIT)
			o->flags |= TMP_MARK;
		memcpy(namebuf, oid_to_hex(&o->oid), GIT_SHA1_HEXSZ);
		if (write_in_full(cmd->in, namebuf, GIT_SHA1_HEXSZ + 1) < 0)
			goto error;
	}
	close(cmd->in);
	cmd->in = -1;
	sigchain_pop(SIGPIPE);

	return 0;

error:
	sigchain_pop(SIGPIPE);

	if (cmd->in >= 0)
		close(cmd->in);
	if (cmd->out >= 0)
		close(cmd->out);
	return -1;
}