 	if (flags && !starts_with(name, "refs/heads/") &&
 			!starts_with(name, "refs/tags/"))
 		return 0;
 
 	strbuf_addstr(buf, name);
 	if (safe_create_leading_directories(buf->buf) ||
-	    write_file(buf->buf, 0, "%s\n", oid_to_hex(oid)))
+	    write_file_gently(buf->buf, "%s", oid_to_hex(oid)))
 		return error("problems writing temporary file %s: %s",
 			     buf->buf, strerror(errno));
 	strbuf_setlen(buf, len);
 	return 0;
 }
 
