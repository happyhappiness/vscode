 
 	if (!pack_name && !from_stdin)
 		usage(index_pack_usage);
 	if (fix_thin_pack && !from_stdin)
 		die(_("--fix-thin cannot be used without --stdin"));
 	if (!index_name && pack_name) {
-		int len = strlen(pack_name);
-		if (!has_extension(pack_name, ".pack"))
+		size_t len;
+		if (!strip_suffix(pack_name, ".pack", &len))
 			die(_("packfile name '%s' does not end with '.pack'"),
 			    pack_name);
-		index_name_buf = xmalloc(len);
-		memcpy(index_name_buf, pack_name, len - 5);
-		strcpy(index_name_buf + len - 5, ".idx");
-		index_name = index_name_buf;
+		strbuf_add(&index_name_buf, pack_name, len);
+		strbuf_addstr(&index_name_buf, ".idx");
+		index_name = index_name_buf.buf;
 	}
 	if (keep_msg && !keep_name && pack_name) {
-		int len = strlen(pack_name);
-		if (!has_extension(pack_name, ".pack"))
+		size_t len;
+		if (!strip_suffix(pack_name, ".pack", &len))
 			die(_("packfile name '%s' does not end with '.pack'"),
 			    pack_name);
-		keep_name_buf = xmalloc(len);
-		memcpy(keep_name_buf, pack_name, len - 5);
-		strcpy(keep_name_buf + len - 5, ".keep");
-		keep_name = keep_name_buf;
+		strbuf_add(&keep_name_buf, pack_name, len);
+		strbuf_addstr(&keep_name_buf, ".idx");
+		keep_name = keep_name_buf.buf;
 	}
 	if (verify) {
 		if (!index_name)
 			die(_("--verify with no packfile name given"));
 		read_idx_option(&opts, index_name);
 		opts.flags |= WRITE_IDX_VERIFY | WRITE_IDX_STRICT;
