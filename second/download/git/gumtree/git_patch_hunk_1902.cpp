 	if (server_supports("quiet"))
 		quiet_supported = 1;
 	if (server_supports("agent"))
 		agent_supported = 1;
 	if (server_supports("no-thin"))
 		args->use_thin_pack = 0;
+	if (args->push_cert) {
+		int len;
+
+		push_cert_nonce = server_feature_value("push-cert", &len);
+		if (!push_cert_nonce)
+			die(_("the receiving end does not support --signed push"));
+		push_cert_nonce = xmemdupz(push_cert_nonce, len);
+	}
 
 	if (!remote_refs) {
 		fprintf(stderr, "No refs in common and none specified; doing nothing.\n"
 			"Perhaps you should specify a branch such as 'master'.\n");
 		return 0;
 	}
 
+	if (status_report)
+		strbuf_addstr(&cap_buf, " report-status");
+	if (use_sideband)
+		strbuf_addstr(&cap_buf, " side-band-64k");
+	if (quiet_supported && (args->quiet || !args->progress))
+		strbuf_addstr(&cap_buf, " quiet");
+	if (agent_supported)
+		strbuf_addf(&cap_buf, " agent=%s", git_user_agent_sanitized());
+
+	/*
+	 * NEEDSWORK: why does delete-refs have to be so specific to
+	 * send-pack machinery that set_ref_status_for_push() cannot
+	 * set this bit for us???
+	 */
+	for (ref = remote_refs; ref; ref = ref->next)
+		if (ref->deletion && !allow_deleting_refs)
+			ref->status = REF_STATUS_REJECT_NODELETE;
+
 	if (!args->dry_run)
 		advertise_shallow_grafts_buf(&req_buf);
 
+	if (!args->dry_run && args->push_cert)
+		cmds_sent = generate_push_cert(&req_buf, remote_refs, args,
+					       cap_buf.buf, push_cert_nonce);
+
 	/*
-	 * Finally, tell the other end!
+	 * Clear the status for each ref and see if we need to send
+	 * the pack data.
 	 */
-	new_refs = 0;
 	for (ref = remote_refs; ref; ref = ref->next) {
-		if (!ref->peer_ref && !args->send_mirror)
+		if (!ref_update_to_be_sent(ref, args))
 			continue;
 
-		/* Check for statuses set by set_ref_status_for_push() */
-		switch (ref->status) {
-		case REF_STATUS_REJECT_NONFASTFORWARD:
-		case REF_STATUS_REJECT_ALREADY_EXISTS:
-		case REF_STATUS_REJECT_FETCH_FIRST:
-		case REF_STATUS_REJECT_NEEDS_FORCE:
-		case REF_STATUS_REJECT_STALE:
-		case REF_STATUS_UPTODATE:
-			continue;
-		default:
-			; /* do nothing */
-		}
+		if (!ref->deletion)
+			need_pack_data = 1;
 
-		if (ref->deletion && !allow_deleting_refs) {
-			ref->status = REF_STATUS_REJECT_NODELETE;
+		if (args->dry_run || !status_report)
+			ref->status = REF_STATUS_OK;
+		else
+			ref->status = REF_STATUS_EXPECTING_REPORT;
+	}
+
+	/*
+	 * Finally, tell the other end!
+	 */
+	for (ref = remote_refs; ref; ref = ref->next) {
+		char *old_hex, *new_hex;
+
+		if (args->dry_run || args->push_cert)
 			continue;
-		}
 
-		if (!ref->deletion)
-			new_refs++;
+		if (!ref_update_to_be_sent(ref, args))
+			continue;
 
-		if (args->dry_run) {
-			ref->status = REF_STATUS_OK;
+		old_hex = sha1_to_hex(ref->old_sha1);
+		new_hex = sha1_to_hex(ref->new_sha1);
+		if (!cmds_sent) {
+			packet_buf_write(&req_buf,
+					 "%s %s %s%c%s",
+					 old_hex, new_hex, ref->name, 0,
+					 cap_buf.buf);
+			cmds_sent = 1;
 		} else {
-			char *old_hex = sha1_to_hex(ref->old_sha1);
-			char *new_hex = sha1_to_hex(ref->new_sha1);
-			int quiet = quiet_supported && (args->quiet || !args->progress);
-
-			if (!cmds_sent && (status_report || use_sideband ||
-					   quiet || agent_supported)) {
-				packet_buf_write(&req_buf,
-						 "%s %s %s%c%s%s%s%s%s",
-						 old_hex, new_hex, ref->name, 0,
-						 status_report ? " report-status" : "",
-						 use_sideband ? " side-band-64k" : "",
-						 quiet ? " quiet" : "",
-						 agent_supported ? " agent=" : "",
-						 agent_supported ? git_user_agent_sanitized() : ""
-						);
-			}
-			else
-				packet_buf_write(&req_buf, "%s %s %s",
-						 old_hex, new_hex, ref->name);
-			ref->status = status_report ?
-				REF_STATUS_EXPECTING_REPORT :
-				REF_STATUS_OK;
-			cmds_sent++;
+			packet_buf_write(&req_buf, "%s %s %s",
+					 old_hex, new_hex, ref->name);
 		}
 	}
 
 	if (args->stateless_rpc) {
 		if (!args->dry_run && (cmds_sent || is_repository_shallow())) {
 			packet_buf_flush(&req_buf);
