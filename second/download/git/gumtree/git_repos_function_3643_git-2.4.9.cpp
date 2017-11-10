static int find_common(struct fetch_pack_args *args,
		       int fd[2], unsigned char *result_sha1,
		       struct ref *refs)
{
	int fetching;
	int count = 0, flushes = 0, flush_at = INITIAL_FLUSH, retval;
	const unsigned char *sha1;
	unsigned in_vain = 0;
	int got_continue = 0;
	int got_ready = 0;
	struct strbuf req_buf = STRBUF_INIT;
	size_t state_len = 0;

	if (args->stateless_rpc && multi_ack == 1)
		die("--stateless-rpc requires multi_ack_detailed");
	if (marked)
		for_each_ref(clear_marks, NULL);
	marked = 1;

	for_each_ref(rev_list_insert_ref, NULL);
	for_each_alternate_ref(insert_one_alternate_ref, NULL);

	fetching = 0;
	for ( ; refs ; refs = refs->next) {
		unsigned char *remote = refs->old_sha1;
		const char *remote_hex;
		struct object *o;

		/*
		 * If that object is complete (i.e. it is an ancestor of a
		 * local ref), we tell them we have it but do not have to
		 * tell them about its ancestors, which they already know
		 * about.
		 *
		 * We use lookup_object here because we are only
		 * interested in the case we *know* the object is
		 * reachable and we have already scanned it.
		 */
		if (((o = lookup_object(remote)) != NULL) &&
				(o->flags & COMPLETE)) {
			continue;
		}

		remote_hex = sha1_to_hex(remote);
		if (!fetching) {
			struct strbuf c = STRBUF_INIT;
			if (multi_ack == 2)     strbuf_addstr(&c, " multi_ack_detailed");
			if (multi_ack == 1)     strbuf_addstr(&c, " multi_ack");
			if (no_done)            strbuf_addstr(&c, " no-done");
			if (use_sideband == 2)  strbuf_addstr(&c, " side-band-64k");
			if (use_sideband == 1)  strbuf_addstr(&c, " side-band");
			if (args->use_thin_pack) strbuf_addstr(&c, " thin-pack");
			if (args->no_progress)   strbuf_addstr(&c, " no-progress");
			if (args->include_tag)   strbuf_addstr(&c, " include-tag");
			if (prefer_ofs_delta)   strbuf_addstr(&c, " ofs-delta");
			if (agent_supported)    strbuf_addf(&c, " agent=%s",
							    git_user_agent_sanitized());
			packet_buf_write(&req_buf, "want %s%s\n", remote_hex, c.buf);
			strbuf_release(&c);
		} else
			packet_buf_write(&req_buf, "want %s\n", remote_hex);
		fetching++;
	}

	if (!fetching) {
		strbuf_release(&req_buf);
		packet_flush(fd[1]);
		return 1;
	}

	if (is_repository_shallow())
		write_shallow_commits(&req_buf, 1, NULL);
	if (args->depth > 0)
		packet_buf_write(&req_buf, "deepen %d", args->depth);
	packet_buf_flush(&req_buf);
	state_len = req_buf.len;

	if (args->depth > 0) {
		char *line;
		const char *arg;
		unsigned char sha1[20];

		send_request(args, fd[1], &req_buf);
		while ((line = packet_read_line(fd[0], NULL))) {
			if (skip_prefix(line, "shallow ", &arg)) {
				if (get_sha1_hex(arg, sha1))
					die("invalid shallow line: %s", line);
				register_shallow(sha1);
				continue;
			}
			if (skip_prefix(line, "unshallow ", &arg)) {
				if (get_sha1_hex(arg, sha1))
					die("invalid unshallow line: %s", line);
				if (!lookup_object(sha1))
					die("object not found: %s", line);
				/* make sure that it is parsed as shallow */
				if (!parse_object(sha1))
					die("error in object: %s", line);
				if (unregister_shallow(sha1))
					die("no shallow found: %s", line);
				continue;
			}
			die("expected shallow/unshallow, got %s", line);
		}
	} else if (!args->stateless_rpc)
		send_request(args, fd[1], &req_buf);

	if (!args->stateless_rpc) {
		/* If we aren't using the stateless-rpc interface
		 * we don't need to retain the headers.
		 */
		strbuf_setlen(&req_buf, 0);
		state_len = 0;
	}

	flushes = 0;
	retval = -1;
	while ((sha1 = get_rev())) {
		packet_buf_write(&req_buf, "have %s\n", sha1_to_hex(sha1));
		if (args->verbose)
			fprintf(stderr, "have %s\n", sha1_to_hex(sha1));
		in_vain++;
		if (flush_at <= ++count) {
			int ack;

			packet_buf_flush(&req_buf);
			send_request(args, fd[1], &req_buf);
			strbuf_setlen(&req_buf, state_len);
			flushes++;
			flush_at = next_flush(args, count);

			/*
			 * We keep one window "ahead" of the other side, and
			 * will wait for an ACK only on the next one
			 */
			if (!args->stateless_rpc && count == INITIAL_FLUSH)
				continue;

			consume_shallow_list(args, fd[0]);
			do {
				ack = get_ack(fd[0], result_sha1);
				if (args->verbose && ack)
					fprintf(stderr, "got ack %d %s\n", ack,
							sha1_to_hex(result_sha1));
				switch (ack) {
				case ACK:
					flushes = 0;
					multi_ack = 0;
					retval = 0;
					goto done;
				case ACK_common:
				case ACK_ready:
				case ACK_continue: {
					struct commit *commit =
						lookup_commit(result_sha1);
					if (!commit)
						die("invalid commit %s", sha1_to_hex(result_sha1));
					if (args->stateless_rpc
					 && ack == ACK_common
					 && !(commit->object.flags & COMMON)) {
						/* We need to replay the have for this object
						 * on the next RPC request so the peer knows
						 * it is in common with us.
						 */
						const char *hex = sha1_to_hex(result_sha1);
						packet_buf_write(&req_buf, "have %s\n", hex);
						state_len = req_buf.len;
					}
					mark_common(commit, 0, 1);
					retval = 0;
					in_vain = 0;
					got_continue = 1;
					if (ack == ACK_ready) {
						clear_prio_queue(&rev_list);
						got_ready = 1;
					}
					break;
					}
				}
			} while (ack);
			flushes--;
			if (got_continue && MAX_IN_VAIN < in_vain) {
				if (args->verbose)
					fprintf(stderr, "giving up\n");
				break; /* give up */
			}
		}
	}
done:
	if (!got_ready || !no_done) {
		packet_buf_write(&req_buf, "done\n");
		send_request(args, fd[1], &req_buf);
	}
	if (args->verbose)
		fprintf(stderr, "done\n");
	if (retval != 0) {
		multi_ack = 0;
		flushes++;
	}
	strbuf_release(&req_buf);

	if (!got_ready || !no_done)
		consume_shallow_list(args, fd[0]);
	while (flushes || multi_ack) {
		int ack = get_ack(fd[0], result_sha1);
		if (ack) {
			if (args->verbose)
				fprintf(stderr, "got ack (%d) %s\n", ack,
					sha1_to_hex(result_sha1));
			if (ack == ACK)
				return 0;
			multi_ack = 1;
			continue;
		}
		flushes--;
	}
	/* it is no error to fetch into a completely empty repo */
	return count ? retval : 0;
}