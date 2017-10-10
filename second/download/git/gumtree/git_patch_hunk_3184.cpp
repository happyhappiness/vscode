 		}
 
 		if (get_sha1_hex(tab - 40, sha1) || tab[-41] != ' ')
 			goto bad_line;
 
 		path_name = ptr;
-		if (line_termination && path_name[0] == '"') {
+		if (!nul_term_line && path_name[0] == '"') {
 			strbuf_reset(&uq);
 			if (unquote_c_style(&uq, path_name, NULL)) {
 				die("git update-index: bad quoting of path name");
 			}
 			path_name = uq.buf;
 		}
