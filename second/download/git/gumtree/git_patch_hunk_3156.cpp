 		allow_missing = 1;
 
 
 	*ntr++ = 0; /* now at the beginning of SHA1 */
 
 	path = ntr + 41;  /* at the beginning of name */
-	if (line_termination && path[0] == '"') {
+	if (!nul_term_line && path[0] == '"') {
 		struct strbuf p_uq = STRBUF_INIT;
 		if (unquote_c_style(&p_uq, path, NULL))
 			die("invalid quoting");
 		path = strbuf_detach(&p_uq, NULL);
 	}
 
