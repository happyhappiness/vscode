static int run_pre_push_hook(struct transport *transport,
			     struct ref *remote_refs)
{
	int ret = 0, x;
	struct ref *r;
	struct child_process proc = CHILD_PROCESS_INIT;
	struct strbuf buf;
	const char *argv[4];

	if (!(argv[0] = find_hook("pre-push")))
		return 0;

	argv[1] = transport->remote->name;
	argv[2] = transport->url;
	argv[3] = NULL;

	proc.argv = argv;
	proc.in = -1;

	if (start_command(&proc)) {
		finish_command(&proc);
		return -1;
	}

	sigchain_push(SIGPIPE, SIG_IGN);

	strbuf_init(&buf, 256);

	for (r = remote_refs; r; r = r->next) {
		if (!r->peer_ref) continue;
		if (r->status == REF_STATUS_REJECT_NONFASTFORWARD) continue;
		if (r->status == REF_STATUS_REJECT_STALE) continue;
		if (r->status == REF_STATUS_UPTODATE) continue;

		strbuf_reset(&buf);
		strbuf_addf( &buf, "%s %s %s %s\n",
			 r->peer_ref->name, oid_to_hex(&r->new_oid),
			 r->name, oid_to_hex(&r->old_oid));

		if (write_in_full(proc.in, buf.buf, buf.len) < 0) {
			/* We do not mind if a hook does not read all refs. */
			if (errno != EPIPE)
				ret = -1;
			break;
		}
	}

	strbuf_release(&buf);

	x = close(proc.in);
	if (!ret)
		ret = x;

	sigchain_pop(SIGPIPE);

	x = finish_command(&proc);
	if (!ret)
		ret = x;

	return ret;
}