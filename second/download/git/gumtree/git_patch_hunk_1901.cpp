 {
 	if (!is_repository_shallow())
 		return;
 	for_each_commit_graft(advertise_shallow_grafts_cb, sb);
 }
 
+static int ref_update_to_be_sent(const struct ref *ref, const struct send_pack_args *args)
+{
+	if (!ref->peer_ref && !args->send_mirror)
+		return 0;
+
+	/* Check for statuses set by set_ref_status_for_push() */
+	switch (ref->status) {
+	case REF_STATUS_REJECT_NONFASTFORWARD:
+	case REF_STATUS_REJECT_ALREADY_EXISTS:
+	case REF_STATUS_REJECT_FETCH_FIRST:
+	case REF_STATUS_REJECT_NEEDS_FORCE:
+	case REF_STATUS_REJECT_STALE:
+	case REF_STATUS_REJECT_NODELETE:
+	case REF_STATUS_UPTODATE:
+		return 0;
+	default:
+		return 1;
+	}
+}
+
+/*
+ * the beginning of the next line, or the end of buffer.
+ *
+ * NEEDSWORK: perhaps move this to git-compat-util.h or somewhere and
+ * convert many similar uses found by "git grep -A4 memchr".
+ */
+static const char *next_line(const char *line, size_t len)
+{
+	const char *nl = memchr(line, '\n', len);
+	if (!nl)
+		return line + len; /* incomplete line */
+	return nl + 1;
+}
+
+static int generate_push_cert(struct strbuf *req_buf,
+			      const struct ref *remote_refs,
+			      struct send_pack_args *args,
+			      const char *cap_string,
+			      const char *push_cert_nonce)
+{
+	const struct ref *ref;
+	char *signing_key = xstrdup(get_signing_key());
+	const char *cp, *np;
+	struct strbuf cert = STRBUF_INIT;
+	int update_seen = 0;
+
+	strbuf_addf(&cert, "certificate version 0.1\n");
+	strbuf_addf(&cert, "pusher %s ", signing_key);
+	datestamp(&cert);
+	strbuf_addch(&cert, '\n');
+	if (args->url && *args->url) {
+		char *anon_url = transport_anonymize_url(args->url);
+		strbuf_addf(&cert, "pushee %s\n", anon_url);
+		free(anon_url);
+	}
+	if (push_cert_nonce[0])
+		strbuf_addf(&cert, "nonce %s\n", push_cert_nonce);
+	strbuf_addstr(&cert, "\n");
+
+	for (ref = remote_refs; ref; ref = ref->next) {
+		if (!ref_update_to_be_sent(ref, args))
+			continue;
+		update_seen = 1;
+		strbuf_addf(&cert, "%s %s %s\n",
+			    sha1_to_hex(ref->old_sha1),
+			    sha1_to_hex(ref->new_sha1),
+			    ref->name);
+	}
+	if (!update_seen)
+		goto free_return;
+
+	if (sign_buffer(&cert, &cert, signing_key))
+		die(_("failed to sign the push certificate"));
+
+	packet_buf_write(req_buf, "push-cert%c%s", 0, cap_string);
+	for (cp = cert.buf; cp < cert.buf + cert.len; cp = np) {
+		np = next_line(cp, cert.buf + cert.len - cp);
+		packet_buf_write(req_buf,
+				 "%.*s", (int)(np - cp), cp);
+	}
+	packet_buf_write(req_buf, "push-cert-end\n");
+
+free_return:
+	free(signing_key);
+	strbuf_release(&cert);
+	return update_seen;
+}
+
 int send_pack(struct send_pack_args *args,
 	      int fd[], struct child_process *conn,
 	      struct ref *remote_refs,
 	      struct sha1_array *extra_have)
 {
 	int in = fd[0];
 	int out = fd[1];
 	struct strbuf req_buf = STRBUF_INIT;
+	struct strbuf cap_buf = STRBUF_INIT;
 	struct ref *ref;
-	int new_refs;
+	int need_pack_data = 0;
 	int allow_deleting_refs = 0;
 	int status_report = 0;
 	int use_sideband = 0;
 	int quiet_supported = 0;
 	int agent_supported = 0;
 	unsigned cmds_sent = 0;
 	int ret;
 	struct async demux;
+	const char *push_cert_nonce = NULL;
 
 	/* Does the other end support the reporting? */
 	if (server_supports("report-status"))
 		status_report = 1;
 	if (server_supports("delete-refs"))
 		allow_deleting_refs = 1;
