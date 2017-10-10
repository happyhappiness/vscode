 			     chain_histogram[i]),
 			  i + 1,
 			  chain_histogram[i]);
 	}
 }
 
+static const char *derive_filename(const char *pack_name, const char *suffix,
+				   struct strbuf *buf)
+{
+	size_t len;
+	if (!strip_suffix(pack_name, ".pack", &len))
+		die(_("packfile name '%s' does not end with '.pack'"),
+		    pack_name);
+	strbuf_add(buf, pack_name, len);
+	strbuf_addstr(buf, suffix);
+	return buf->buf;
+}
+
 int cmd_index_pack(int argc, const char **argv, const char *prefix)
 {
 	int i, fix_thin_pack = 0, verify = 0, stat_only = 0;
 	const char *curr_index;
 	const char *index_name = NULL, *pack_name = NULL;
 	const char *keep_name = NULL, *keep_msg = NULL;
