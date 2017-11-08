int send_pack(struct send_pack_args *args,
	      int fd[], struct child_process *conn,
	      struct ref *remote_refs,
	      struct oid_array *extra_have)
{
	int in = fd[0];
	int out = fd[1];
	struct strbuf req_buf = STRBUF_INIT;
	struct strbuf cap_buf = STRBUF_INIT;
	struct ref *ref;
	int need_pack_data = 0;
	int allow_deleting_refs = 0;
	int status_report = 0;
	int use_sideband = 0;
	int quiet_supported = 0;
	int agent_supported = 0;
	int use_atomic = 0;
	int atomic_supported = 0;
	int use_push_options = 0;
	int push_options_supported = 0;
	unsigned cmds_sent = 0;
	int ret;
	struct async demux;
	const char *push_cert_nonce = NULL;

	/* Does the other end support the reporting? */
	if (server_supports("report-status"))
		status_report = 1;
	if (server_supports("delete-refs"))
		allow_deleting_refs = 1;
	if (server_supports("ofs-delta"))
		args->use_ofs_delta = 1;
	if (server_supports("side-band-64k"))
		use_sideband = 1;
	if (server_supports("quiet"))
		quiet_supported = 1;
	if (server_supports("agent"))
		agent_supported = 1;
	if (server_supports("no-thin"))
		args->use_thin_pack = 0;
	if (server_supports("atomic"))
		atomic_supported = 1;
	if (server_supports("push-options"))
		push_options_supported = 1;

	if (args->push_cert != SEND_PACK_PUSH_CERT_NEVER) {
		int len;
		push_cert_nonce = server_feature_value("push-cert", &len);
		if (push_cert_nonce) {
			reject_invalid_nonce(push_cert_nonce, len);
			push_cert_nonce = xmemdupz(push_cert_nonce, len);
		} else if (args->push_cert == SEND_PACK_PUSH_CERT_ALWAYS) {
			die(_("the receiving end does not support --signed push"));
		} else if (args->push_cert == SEND_PACK_PUSH_CERT_IF_ASKED) {
			warning(_("not sending a push certificate since the"
				  " receiving end does not support --signed"
				  " push"));
		}
	}

	if (!remote_refs) {
		fprintf(stderr, "No refs in common and none specified; doing nothing.\n"
			"Perhaps you should specify a branch such as 'master'.\n");
		return 0;
	}
	if (args->atomic && !atomic_supported)
		die(_("the receiving end does not support --atomic push"));

	use_atomic = atomic_supported && args->atomic;

	if (args->push_options && !push_options_supported)
		die(_("the receiving end does not support push options"));

	use_push_options = push_options_supported && args->push_options;

	if (status_report)
		strbuf_addstr(&cap_buf, " report-status");
	if (use_sideband)
		strbuf_addstr(&cap_buf, " side-band-64k");
	if (quiet_supported && (args->quiet || !args->progress))
		strbuf_addstr(&cap_buf, " quiet");
	if (use_atomic)
		strbuf_addstr(&cap_buf, " atomic");
	if (use_push_options)
		strbuf_addstr(&cap_buf, " push-options");
	if (agent_supported)
		strbuf_addf(&cap_buf, " agent=%s", git_user_agent_sanitized());

	/*
	 * NEEDSWORK: why does delete-refs have to be so specific to
	 * send-pack machinery that set_ref_status_for_push() cannot
	 * set this bit for us???
	 */
	for (ref = remote_refs; ref; ref = ref->next)
		if (ref->deletion && !allow_deleting_refs)
			ref->status = REF_STATUS_REJECT_NODELETE;

	if (!args->dry_run)
		advertise_shallow_grafts_buf(&req_buf);

	if (!args->dry_run && push_cert_nonce)
		cmds_sent = generate_push_cert(&req_buf, remote_refs, args,
					       cap_buf.buf, push_cert_nonce);

	/*
	 * Clear the status for each ref and see if we need to send
	 * the pack data.
	 */
	for (ref = remote_refs; ref; ref = ref->next) {
		switch (check_to_send_update(ref, args)) {
		case 0: /* no error */
			break;
		case CHECK_REF_STATUS_REJECTED:
			/*
			 * When we know the server would reject a ref update if
			 * we were to send it and we're trying to send the refs
			 * atomically, abort the whole operation.
			 */
			if (use_atomic)
				return atomic_push_failure(args, remote_refs, ref);
			/* Fallthrough for non atomic case. */
		default:
			continue;
		}
		if (!ref->deletion)
			need_pack_data = 1;

		if (args->dry_run || !status_report)
			ref->status = REF_STATUS_OK;
		else
			ref->status = REF_STATUS_EXPECTING_REPORT;
	}

	/*
	 * Finally, tell the other end!
	 */
	for (ref = remote_refs; ref; ref = ref->next) {
		char *