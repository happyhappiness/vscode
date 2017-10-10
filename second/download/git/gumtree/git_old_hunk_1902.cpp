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
