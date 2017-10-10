 
 	if (strcmp(var, "receive.shallowupdate") == 0) {
 		shallow_update = git_config_bool(var, value);
 		return 0;
 	}
 
+	if (strcmp(var, "receive.certnonceseed") == 0)
+		return git_config_string(&cert_nonce_seed, var, value);
+
+	if (strcmp(var, "receive.certnonceslop") == 0) {
+		nonce_stamp_slop_limit = git_config_ulong(var, value);
+		return 0;
+	}
+
 	return git_default_config(var, value, cb);
 }
 
 static void show_ref(const char *path, const unsigned char *sha1)
 {
 	if (ref_is_hidden(path))
 		return;
 
-	if (sent_capabilities)
+	if (sent_capabilities) {
 		packet_write(1, "%s %s\n", sha1_to_hex(sha1), path);
-	else
-		packet_write(1, "%s %s%c%s%s agent=%s\n",
-			     sha1_to_hex(sha1), path, 0,
-			     " report-status delete-refs side-band-64k quiet",
-			     prefer_ofs_delta ? " ofs-delta" : "",
-			     git_user_agent_sanitized());
-	sent_capabilities = 1;
+	} else {
+		struct strbuf cap = STRBUF_INIT;
+
+		strbuf_addstr(&cap,
+			      "report-status delete-refs side-band-64k quiet");
+		if (prefer_ofs_delta)
+			strbuf_addstr(&cap, " ofs-delta");
+		if (push_cert_nonce)
+			strbuf_addf(&cap, " push-cert=%s", push_cert_nonce);
+		strbuf_addf(&cap, " agent=%s", git_user_agent_sanitized());
+		packet_write(1, "%s %s%c%s\n",
+			     sha1_to_hex(sha1), path, 0, cap.buf);
+		strbuf_release(&cap);
+		sent_capabilities = 1;
+	}
 }
 
 static int show_ref_cb(const char *path, const unsigned char *sha1, int flag, void *unused)
 {
 	path = strip_namespace(path);
 	/*
