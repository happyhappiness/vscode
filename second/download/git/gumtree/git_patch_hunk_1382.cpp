 		goto abort;
 	}
 
 	/* The bundle header ends with an empty line */
 	while (!strbuf_getwholeline_fd(&buf, fd, '\n') &&
 	       buf.len && buf.buf[0] != '\n') {
-		unsigned char sha1[20];
+		struct object_id oid;
 		int is_prereq = 0;
+		const char *p;
 
 		if (*buf.buf == '-') {
 			is_prereq = 1;
 			strbuf_remove(&buf, 0, 1);
 		}
 		strbuf_rtrim(&buf);
 
 		/*
 		 * Tip lines have object name, SP, and refname.
 		 * Prerequisites have object name that is optionally
 		 * followed by SP and subject line.
 		 */
-		if (get_sha1_hex(buf.buf, sha1) ||
-		    (buf.len > 40 && !isspace(buf.buf[40])) ||
-		    (!is_prereq && buf.len <= 40)) {
+		if (parse_oid_hex(buf.buf, &oid, &p) ||
+		    (*p && !isspace(*p)) ||
+		    (!is_prereq && !*p)) {
 			if (report_path)
 				error(_("unrecognized header: %s%s (%d)"),
 				      (is_prereq ? "-" : ""), buf.buf, (int)buf.len);
 			status = -1;
 			break;
 		} else {
 			if (is_prereq)
-				add_to_ref_list(sha1, "", &header->prerequisites);
+				add_to_ref_list(&oid, "", &header->prerequisites);
 			else
-				add_to_ref_list(sha1, buf.buf + 41, &header->references);
+				add_to_ref_list(&oid, p + 1, &header->references);
 		}
 	}
 
  abort:
 	if (status) {
 		close(fd);
