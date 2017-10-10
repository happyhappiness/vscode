 	assert(ca.drv);
 	assert(ca.drv->clean);
 
 	if (!apply_filter(path, NULL, 0, fd, dst, ca.drv->clean))
 		die("%s: clean filter '%s' failed", path, ca.drv->name);
 
-	ca.crlf_action = input_crlf_action(ca.crlf_action, ca.eol_attr);
 	crlf_to_git(path, dst->buf, dst->len, dst, ca.crlf_action, checksafe);
 	ident_to_git(path, dst->buf, dst->len, dst, ca.ident);
 }
 
 static int convert_to_working_tree_internal(const char *path, const char *src,
 					    size_t len, struct strbuf *dst,
