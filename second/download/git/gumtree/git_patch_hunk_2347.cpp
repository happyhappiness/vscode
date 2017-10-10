 	if (!symref->nr)
 		return;
 	for_each_string_list_item(item, symref)
 		strbuf_addf(buf, " symref=%s:%s", item->string, (char *)item->util);
 }
 
-static int send_ref(const char *refname, const unsigned char *sha1, int flag, void *cb_data)
+static int send_ref(const char *refname, const struct object_id *oid,
+		    int flag, void *cb_data)
 {
 	static const char *capabilities = "multi_ack thin-pack side-band"
 		" side-band-64k ofs-delta shallow no-progress"
 		" include-tag multi_ack_detailed";
 	const char *refname_nons = strip_namespace(refname);
-	unsigned char peeled[20];
+	struct object_id peeled;
 
-	if (mark_our_ref(refname, sha1))
+	if (mark_our_ref(refname, oid))
 		return 0;
 
 	if (capabilities) {
 		struct strbuf symref_info = STRBUF_INIT;
 
 		format_symref_info(&symref_info, cb_data);
-		packet_write(1, "%s %s%c%s%s%s%s agent=%s\n",
-			     sha1_to_hex(sha1), refname_nons,
+		packet_write(1, "%s %s%c%s%s%s%s%s agent=%s\n",
+			     oid_to_hex(oid), refname_nons,
 			     0, capabilities,
-			     allow_tip_sha1_in_want ? " allow-tip-sha1-in-want" : "",
+			     (allow_unadvertised_object_request & ALLOW_TIP_SHA1) ?
+				     " allow-tip-sha1-in-want" : "",
+			     (allow_unadvertised_object_request & ALLOW_REACHABLE_SHA1) ?
+				     " allow-reachable-sha1-in-want" : "",
 			     stateless_rpc ? " no-done" : "",
 			     symref_info.buf,
 			     git_user_agent_sanitized());
 		strbuf_release(&symref_info);
 	} else {
-		packet_write(1, "%s %s\n", sha1_to_hex(sha1), refname_nons);
+		packet_write(1, "%s %s\n", oid_to_hex(oid), refname_nons);
 	}
 	capabilities = NULL;
-	if (!peel_ref(refname, peeled))
-		packet_write(1, "%s %s^{}\n", sha1_to_hex(peeled), refname_nons);
+	if (!peel_ref(refname, peeled.hash))
+		packet_write(1, "%s %s^{}\n", oid_to_hex(&peeled), refname_nons);
 	return 0;
 }
 
-static int find_symref(const char *refname, const unsigned char *sha1, int flag,
-		       void *cb_data)
+static int find_symref(const char *refname, const struct object_id *oid,
+		       int flag, void *cb_data)
 {
 	const char *symref_target;
 	struct string_list_item *item;
-	unsigned char unused[20];
+	struct object_id unused;
 
 	if ((flag & REF_ISSYMREF) == 0)
 		return 0;
-	symref_target = resolve_ref_unsafe(refname, 0, unused, &flag);
+	symref_target = resolve_ref_unsafe(refname, 0, unused.hash, &flag);
 	if (!symref_target || (flag & REF_ISSYMREF) == 0)
 		die("'%s' is a symref but it is not?", refname);
 	item = string_list_append(cb_data, refname);
 	item->util = xstrdup(symref_target);
 	return 0;
 }
