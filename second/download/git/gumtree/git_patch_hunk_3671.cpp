 			oid = &merge_remote_util(c)->obj->oid;
 		} else {
 			oid = &c->object.oid;
 		}
 		strbuf_addf(&buf, "%s\n", oid_to_hex(oid));
 	}
-	filename = git_path_merge_head();
-	fd = open(filename, O_WRONLY | O_CREAT, 0666);
-	if (fd < 0)
-		die_errno(_("Could not open '%s' for writing"), filename);
-	if (write_in_full(fd, buf.buf, buf.len) != buf.len)
-		die_errno(_("Could not write to '%s'"), filename);
-	close(fd);
+	write_file_buf(git_path_merge_head(), buf.buf, buf.len);
 	strbuf_addch(&merge_msg, '\n');
-	write_merge_msg(&merge_msg);
+	write_file_buf(git_path_merge_msg(), merge_msg.buf, merge_msg.len);
 
-	filename = git_path_merge_mode();
-	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
-	if (fd < 0)
-		die_errno(_("Could not open '%s' for writing"), filename);
 	strbuf_reset(&buf);
 	if (fast_forward == FF_NO)
 		strbuf_addf(&buf, "no-ff");
-	if (write_in_full(fd, buf.buf, buf.len) != buf.len)
-		die_errno(_("Could not write to '%s'"), filename);
-	close(fd);
+	write_file_buf(git_path_merge_mode(), buf.buf, buf.len);
 }
 
 static int default_edit_option(void)
 {
 	static const char name[] = "GIT_MERGE_AUTOEDIT";
 	const char *e = getenv(name);
