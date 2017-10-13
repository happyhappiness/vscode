int send_pack(struct send_pack_args *args,
	      int fd[], struct child_process *conn,
	      struct ref *remote_refs,
	      struct sha1_array *extra_have)
{
	int in = fd[0];
	int out = fd[1];
	struct strbuf req_buf = STRBUF_INIT;
	struct ref *ref;
	int new_refs;
	int allow_deleting_refs = 0;
	int status_report = 0;
	int use_sideband = 0;
	int quiet_supported = 0;
	int agent_supported = 0;
	unsigned cmds_sent = 0;
	int ret;
	struct async demux;

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

	if (!remote_refs) {
		fprintf(stderr, "No refs in common and none specified; doing nothing.\n"
			"Perhaps you should specify a branch such as 'master'.\n");
		return 0;
	}

	if (!args->dry_run)
		advertise_shallow_grafts_buf(&req_buf);

	/*
	 * Finally, tell the other end!
	 */
	new_refs = 0;
	for (ref = remote_refs; ref; ref = ref->next) {
		if (!ref->peer_ref && !args->send_mirror)
			continue;

		/* Check for statuses set by set_ref_status_for_push() */
		switch (ref->status) {
		case REF_STATUS_REJECT_NONFASTFORWARD:
		case REF_STATUS_REJECT_ALREADY_EXISTS:
		case REF_STATUS_REJECT_FETCH_FIRST:
		case REF_STATUS_REJECT_NEEDS_FORCE:
		case REF_STATUS_REJECT_STALE:
		case REF_STATUS_UPTODATE:
			continue;
		default:
			; /* do nothing */
		}

		if (ref->deletion && !allow_deleting_refs) {
			ref->status = REF_STATUS_REJECT_NODELETE;
			continue;
		}

		if (!ref->deletion)
			new_refs++;

		if (args->dry_run) {
			ref->status = REF_STATUS_OK;
		} else {
			char *old_hex = sha1_to_hex(ref->old_sha1);
			char *new_hex = sha1_to_hex(ref->new_sha1);
			int quiet = quiet_supported && (args->quiet || !args->progress);

			if (!cmds_sent && (status_report || use_sideband ||
					   quiet || agent_supported)) {
				packet_buf_write(&req_buf,
						 "%s %s %s%c%s%s%s%s%s",
						 old_hex, new_hex, ref->name, 0,
						 status_report ? " report-status" : "",
						 use_sideband ? " side-band-64k" : "",
						 quiet ? " quiet" : "",
						 agent_supported ? " agent=" : "",
						 agent_supported ? git_user_agent_sanitized() : ""
						);
			}
			else
				packet_buf_write(&req_buf, "%s %s %s",
						 old_hex, new_hex, ref->name);
			ref->status = status_report ?
				REF_STATUS_EXPECTING_REPORT :
				REF_STATUS_OK;
			cmds_sent++;
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

	if (use_sideband && cmds_sent) {
		memset(&demux, 0, sizeof(demux));
		demux.proc = sideband_demux;
		demux.data = fd;
		demux.out = -1;
		if (start_async(&demux))
			die("send-pack: unable to fork off sideband demultiplexer");
		in = demux.out;
	}

	if (new_refs && cmds_sent) {
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