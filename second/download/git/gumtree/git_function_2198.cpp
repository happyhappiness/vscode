int send_pack(struct send_pack_args *args,
	      int fd[], struct child_process *conn,
	      struct ref *remote_refs,
	      struct sha1_array *extra_have)
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

	if (status_report)
		strbuf_addstr(&cap_buf, " report-status");
	if (use_sideband)
		strbuf_addstr(&cap_buf, " side-band-64k");
	if (quiet_supported && (args->quiet || !args->progress))
		strbuf_addstr(&cap_buf, " quiet");
	if (use_atomic)
		strbuf_addstr(&cap_buf, " atomic");
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
		char *old_hex, *new_hex;

		if (args->dry_run || push_cert_nonce)
			continue;

		if (check_to_send_update(ref, args) < 0)
			continue;

		old_hex = sha1_to_hex(ref->old_sha1);
		new_hex = sha1_to_hex(ref->new_sha1);
		if (!cmds_sent) {
			packet_buf_write(&req_buf,
					 "%s %s %s%c%s",
					 old_hex, new_hex, ref->name, 0,
					 cap_buf.buf);
			cmds_sent = 1;
		} else {
			packet_buf_write(&req_buf, "%s %s %s",
					 old_hex, new_hex, ref->name);
		}
	}

	if (args->stateless_rpc) {
		if (!args->dry_run && (cmds_sent || is_repository_shallow())) {
			packet_buf_flush(&req_buf);
			send_sideband(out, -1, req_buf.buf, req_buf.len, LARGE_PACKET_MAX);
		}
	} else {
		write_or_die(out, req_buf.buf, req_buf.len);
		packet_flush(out);
	}
	strbuf_release(&req_buf);
	strbuf_release(&cap_buf);

	if (use_sideband && cmds_sent) {
		memset(&demux, 0, sizeof(demux));
		demux.proc = sideband_demux;
		demux.data = fd;
		demux.out = -1;
		if (start_async(&demux))
			die("send-pack: unable to fork off sideband demultiplexer");
		in = demux.out;
	}

	if (need_pack_data && cmds_sent) {
		if (pack_objects(out, remote_refs, extra_have, args) < 0) {
			for (ref = remote_refs; ref; ref = ref->next)
				ref->status = REF_STATUS_NONE;
			if (args->stateless_rpc)
				close(out);
			if (git_connection_is_socket(conn))
				shutdown(fd[0], SHUT_WR);
			if (use_sideband)
				finish_async(&demux);
			fd[1] = -1;
			return -1;
		}
		if (!args->stateless_rpc)
			/* Closed by pack_objects() via start_command() */
			fd[1] = -1;
	}
	if (args->stateless_rpc && cmds_sent)
		packet_flush(out);

	if (status_report && cmds_sent)
		ret = receive_status(in, remote_refs);
	else
		ret = 0;
	if (args->stateless_rpc)
		packet_flush(out);

	if (use_sideband && cmds_sent) {
		if (finish_async(&demux)) {
			error("error in sideband demultiplexer");
			ret = -1;
		}
		close(demux.out);
	}

	if (ret < 0)
		return ret;

	if (args->porcelain)
		return 0;

	for (ref = remote_refs; ref; ref = ref->next) {
		switch (ref->status) {
		case REF_STATUS_NONE:
		case REF_STATUS_UPTODATE:
		case REF_STATUS_OK:
			break;
		default:
			return -1;
		}
	}
	return 0;
}