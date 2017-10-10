 	pp.date_mode = rev->date_mode;
 	pp_user_info(&pp, "Tagger", &out, buf, get_log_output_encoding());
 	fprintf(rev->diffopt.file, "%s", out.buf);
 	strbuf_release(&out);
 }
 
-static int show_blob_object(const unsigned char *sha1, struct rev_info *rev, const char *obj_name)
+static int show_blob_object(const struct object_id *oid, struct rev_info *rev, const char *obj_name)
 {
-	unsigned char sha1c[20];
+	struct object_id oidc;
 	struct object_context obj_context;
 	char *buf;
 	unsigned long size;
 
 	fflush(rev->diffopt.file);
 	if (!DIFF_OPT_TOUCHED(&rev->diffopt, ALLOW_TEXTCONV) ||
 	    !DIFF_OPT_TST(&rev->diffopt, ALLOW_TEXTCONV))
-		return stream_blob_to_fd(1, sha1, NULL, 0);
+		return stream_blob_to_fd(1, oid, NULL, 0);
 
-	if (get_sha1_with_context(obj_name, 0, sha1c, &obj_context))
+	if (get_sha1_with_context(obj_name, 0, oidc.hash, &obj_context))
 		die(_("Not a valid object name %s"), obj_name);
 	if (!obj_context.path[0] ||
-	    !textconv_object(obj_context.path, obj_context.mode, sha1c, 1, &buf, &size))
-		return stream_blob_to_fd(1, sha1, NULL, 0);
+	    !textconv_object(obj_context.path, obj_context.mode, &oidc, 1, &buf, &size))
+		return stream_blob_to_fd(1, oid, NULL, 0);
 
 	if (!buf)
 		die(_("git show %s: bad file"), obj_name);
 
 	write_or_die(1, buf, size);
 	return 0;
 }
 
-static int show_tag_object(const unsigned char *sha1, struct rev_info *rev)
+static int show_tag_object(const struct object_id *oid, struct rev_info *rev)
 {
 	unsigned long size;
 	enum object_type type;
-	char *buf = read_sha1_file(sha1, &type, &size);
+	char *buf = read_sha1_file(oid->hash, &type, &size);
 	int offset = 0;
 
 	if (!buf)
-		return error(_("Could not read object %s"), sha1_to_hex(sha1));
+		return error(_("Could not read object %s"), oid_to_hex(oid));
 
 	assert(type == OBJ_TAG);
 	while (offset < size && buf[offset] != '\n') {
 		int new_offset = offset + 1;
 		while (new_offset < size && buf[new_offset++] != '\n')
 			; /* do nothing */
