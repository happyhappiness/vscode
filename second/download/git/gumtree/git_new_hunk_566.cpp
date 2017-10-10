{
	int allow_hidden_ref = (allow_unadvertised_object_request &
			(ALLOW_TIP_SHA1 | ALLOW_REACHABLE_SHA1));
	return o->flags & ((allow_hidden_ref ? HIDDEN_REF : 0) | OUR_REF);
}

/*
 * on successful case, it's up to the caller to close cmd->out
 */
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
	namebuf[41] = '\n';
	for (i = get_max_object_index(); 0 < i; ) {
		o = get_indexed_object(--i);
		if (!o)
			continue;
		if (reachable && o->type == OBJ_COMMIT)
			o->flags &= ~TMP_MARK;
		if (!is_our_ref(o))
			continue;
		memcpy(namebuf + 1, oid_to_hex(&o->oid), GIT_SHA1_HEXSZ);
		if (write_in_full(cmd->in, namebuf, 42) < 0)
			goto error;
	}
	namebuf[40] = '\n';
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
		if (write_in_full(cmd->in, namebuf, 41) < 0)
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

static int get_reachable_list(struct object_array *src,
			      struct object_array *reachable)
{
	struct child_process cmd = CHILD_PROCESS_INIT;
	int i;
	struct object *o;
	char namebuf[42]; /* ^ + SHA-1 + LF */

	if (do_reachable_revlist(&cmd, src, reachable) < 0)
		return -1;

	while ((i = read_in_full(cmd.out, namebuf, 41)) == 41) {
		struct object_id sha1;

		if (namebuf[40] != '\n' || get_oid_hex(namebuf, &sha1))
			break;

		o = lookup_object(sha1.hash);
		if (o && o->type == OBJ_COMMIT) {
			o->flags &= ~TMP_MARK;
		}
	}
	for (i = get_max_object_index(); 0 < i; i--) {
		o = get_indexed_object(i - 1);
		if (o && o->type == OBJ_COMMIT &&
		    (o->flags & TMP_MARK)) {
			add_object_array(o, NULL, reachable);
				o->flags &= ~TMP_MARK;
		}
	}
	close(cmd.out);

	if (finish_command(&cmd))
		return -1;

	return 0;
}

static int has_unreachable(struct object_array *src)
{
	struct child_process cmd = CHILD_PROCESS_INIT;
	char buf[1];
	int i;

	if (do_reachable_revlist(&cmd, src, NULL) < 0)
		return 1;

	/*
	 * The commits out of the rev-list are not ancestors of
	 * our ref.
	 */
	i = read_in_full(cmd.out, buf, 1);
	if (i)
		goto error;
	close(cmd.out);
	cmd.out = -1;

	/*
	 * rev-list may have died by encountering a bad commit
	 * in the history, in which case we do want to bail out
	 * even when it showed no commit.
	 */
	if (finish_command(&cmd))
		goto error;

	/* All the non-tip ones are ancestors of what we advertised */
	return 0;

error:
	sigchain_pop(SIGPIPE);
	if (cmd.out >= 0)
		close(cmd.out);
	return 1;
}

static void check_non_tip(void)
{
	int i;

	/*
	 * In the normal in-process case without
	 * uploadpack.allowReachableSHA1InWant,
	 * non-tip requests can never happen.
	 */
	if (!stateless_rpc && !(allow_unadvertised_object_request & ALLOW_REACHABLE_SHA1))
		goto error;
	if (!has_unreachable(&want_obj))
		/* All the non-tip ones are ancestors of what we advertised */
		return;

error:
	/* Pick one of them (we know there at least is one) */
	for (i = 0; i < want_obj.nr; i++) {
		struct object *o = want_obj.objects[i].item;
		if (!is_our_ref(o))
			die("git upload-pack: not our ref %s",
			    oid_to_hex(&o->oid));
	}
}

static void send_shallow(struct commit_list *result)
{
	while (result) {
		struct object *object = &result->item->object;
		if (!(object->flags & (CLIENT_SHALLOW|NOT_SHALLOW))) {
			packet_write_fmt(1, "shallow %s",
					 oid_to_hex(&object->oid));
			register_shallow(object->oid.hash);
			shallow_nr++;
		}
		result = result->next;
	}
}

static void send_unshallow(const struct object_array *shallows)
{
	int i;

	for (i = 0; i < shallows->nr; i++) {
		struct object *object = shallows->objects[i].item;
		if (object->flags & NOT_SHALLOW) {
			struct commit_list *parents;
			packet_write_fmt(1, "unshallow %s",
					 oid_to_hex(&object->oid));
			object->flags &= ~CLIENT_SHALLOW;
			/*
			 * We want to _register_ "object" as shallow, but we
			 * also need to traverse object's parents to deepen a
			 * shallow clone. Unregister it for now so we can
			 * parse and add the parents to the want list, then
			 * re-register it.
			 */
			unregister_shallow(object->oid.hash);
			object->parsed = 0;
			parse_commit_or_die((struct commit *)object);
			parents = ((struct commit *)object)->parents;
			while (parents) {
				add_object_array(&parents->item->object,
						 NULL, &want_obj);
				parents = parents->next;
			}
			add_object_array(object, NULL, &extra_edge_obj);
		}
		/* make sure commit traversal conforms to client */
		register_shallow(object->oid.hash);
	}
}

static void deepen(int depth, int deepen_relative,
		   struct object_array *shallows)
{
	if (depth == INFINITE_DEPTH && !is_repository_shallow()) {
		int i;

		for (i = 0; i < shallows->nr; i++) {
			struct object *object = shallows->objects[i].item;
			object->flags |= NOT_SHALLOW;
		}
	} else if (deepen_relative) {
		struct object_array reachable_shallows = OBJECT_ARRAY_INIT;
		struct commit_list *result;

		get_reachable_list(shallows, &reachable_shallows);
		result = get_shallow_commits(&reachable_shallows,
					     depth + 1,
					     SHALLOW, NOT_SHALLOW);
		send_shallow(result);
		free_commit_list(result);
		object_array_clear(&reachable_shallows);
	} else {
		struct commit_list *result;

		result = get_shallow_commits(&want_obj, depth,
					     SHALLOW, NOT_SHALLOW);
		send_shallow(result);
		free_commit_list(result);
	}

	send_unshallow(shallows);
	packet_flush(1);
}

static void deepen_by_rev_list(int ac, const char **av,
			       struct object_array *shallows)
{
	struct commit_list *result;

	result = get_shallow_commits_by_rev_list(ac, av, SHALLOW, NOT_SHALLOW);
	send_shallow(result);
	free_commit_list(result);
	send_unshallow(shallows);
	packet_flush(1);
}

static void receive_needs(void)
{
	struct object_array shallows = OBJECT_ARRAY_INIT;
	struct string_list deepen_not = STRING_LIST_INIT_DUP;
	int depth = 0;
	int has_non_tip = 0;
	unsigned long deepen_since = 0;
	int deepen_rev_list = 0;

	shallow_nr = 0;
	for (;;) {
		struct object *o;
		const char *features;
		unsigned char sha1_buf[20];
		char *line = packet_read_line(0, NULL);
		const char *arg;

		reset_timeout();
		if (!line)
			break;

		if (skip_prefix(line, "shallow ", &arg)) {
			unsigned char sha1[20];
			struct object *object;
			if (get_sha1_hex(arg, sha1))
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
		if (skip_prefix(line, "deepen ", &arg)) {
			char *end = NULL;
			depth = strtol(arg, &end, 0);
			if (!end || *end || depth <= 0)
				die("Invalid deepen: %s", line);
			continue;
		}
		if (skip_prefix(line, "deepen-since ", &arg)) {
			char *end = NULL;
			deepen_since = strtoul(arg, &end, 0);
			if (!end || *end || !deepen_since ||
			    /* revisions.c's max_age -1 is special */
			    deepen_since == -1)
				die("Invalid deepen-since: %s", line);
			deepen_rev_list = 1;
			continue;
		}
		if (skip_prefix(line, "deepen-not ", &arg)) {
			char *ref = NULL;
			unsigned char sha1[20];
			if (expand_ref(arg, strlen(arg), sha1, &ref) != 1)
				die("git upload-pack: ambiguous deepen-not: %s", line);
			string_list_append(&deepen_not, ref);
			free(ref);
			deepen_rev_list = 1;
			continue;
		}
		if (!skip_prefix(line, "want ", &arg) ||
		    get_sha1_hex(arg, sha1_buf))
			die("git upload-pack: protocol error, "
			    "expected to get sha, not '%s'", line);

		features = arg + 40;

		if (parse_feature_request(features, "deepen-relative"))
			deepen_relative = 1;
		if (parse_feature_request(features, "multi_ack_detailed"))
			multi_ack = 2;
		else if (parse_feature_request(features, "multi_ack"))
			multi_ack = 1;
		if (parse_feature_request(features, "no-done"))
			no_done = 1;
