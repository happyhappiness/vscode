{
	int allow_hidden_ref = (allow_unadvertised_object_request &
			(ALLOW_TIP_SHA1 | ALLOW_REACHABLE_SHA1));
	return o->flags & ((allow_hidden_ref ? HIDDEN_REF : 0) | OUR_REF);
}

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
		memcpy(namebuf + 1, oid_to_hex(&o->oid), GIT_SHA1_HEXSZ);
		if (write_in_full(cmd.in, namebuf, 42) < 0)
			goto error;
	}
	namebuf[40] = '\n';
	for (i = 0; i < want_obj.nr; i++) {
		o = want_obj.objects[i].item;
		if (is_our_ref(o))
			continue;
		memcpy(namebuf, oid_to_hex(&o->oid), GIT_SHA1_HEXSZ);
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
			    oid_to_hex(&o->oid));
	}
}

static void receive_needs(void)
{
	struct object_array shallows = OBJECT_ARRAY_INIT;
	int depth = 0;
	int has_non_tip = 0;

	shallow_nr = 0;
	for (;;) {
		struct object *o;
		const char *features;
		unsigned char sha1_buf[20];
		char *line = packet_read_line(0, NULL);
		reset_timeout();
		if (!line)
			break;

		if (starts_with(line, "shallow ")) {
			unsigned char sha1[20];
			struct object *object;
			if (get_sha1_hex(line + 8, sha1))
				die("invalid shallow line: %s", line);
			object = parse_object(sha1);
			if (!object)
				continue;
			if (object->type != OBJ_COMMIT)
				die("invalid shallow object %s", sha1_to_hex(sha1));
			if (!(object->flags & CLIENT_SHALLOW)) {
				object->flags |= CLIENT_SHALLOW;
				add_object_array(object, NULL, &shallows);
			}
			continue;
		}
		if (starts_with(line, "deepen ")) {
			char *end;
			depth = strtol(line + 7, &end, 0);
			if (end == line + 7 || depth <= 0)
				die("Invalid deepen: %s", line);
			continue;
		}
		if (!starts_with(line, "want ") ||
		    get_sha1_hex(line+5, sha1_buf))
			die("git upload-pack: protocol error, "
			    "expected to get sha, not '%s'", line);

		features = line + 45;

		if (parse_feature_request(features, "multi_ack_detailed"))
			multi_ack = 2;
		else if (parse_feature_request(features, "multi_ack"))
			multi_ack = 1;
		if (parse_feature_request(features, "no-done"))
			no_done = 1;
