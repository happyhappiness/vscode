 		src = dst->buf;
 		len = dst->len;
 	}
 	return ret | ident_to_git(path, src, len, dst, ca.ident);
 }
 
+void convert_to_git_filter_fd(const char *path, int fd, struct strbuf *dst,
+			      enum safe_crlf checksafe)
+{
+	struct conv_attrs ca;
+	convert_attrs(&ca, path);
+
+	assert(ca.drv);
+	assert(ca.drv->clean);
+
+	if (!apply_filter(path, NULL, 0, fd, dst, ca.drv->clean))
+		die("%s: clean filter '%s' failed", path, ca.drv->name);
+
+	ca.crlf_action = input_crlf_action(ca.crlf_action, ca.eol_attr);
+	crlf_to_git(path, dst->buf, dst->len, dst, ca.crlf_action, checksafe);
+	ident_to_git(path, dst->buf, dst->len, dst, ca.ident);
+}
+
 static int convert_to_working_tree_internal(const char *path, const char *src,
 					    size_t len, struct strbuf *dst,
 					    int normalizing)
 {
 	int ret = 0, ret_filter = 0;
 	const char *filter = NULL;
