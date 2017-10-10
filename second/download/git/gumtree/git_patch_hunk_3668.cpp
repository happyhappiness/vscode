 	while ((commit = get_revision(&rev)) != NULL) {
 		strbuf_addch(&out, '\n');
 		strbuf_addf(&out, "commit %s\n",
 			oid_to_hex(&commit->object.oid));
 		pretty_print_commit(&ctx, commit, &out);
 	}
-	if (write_in_full(fd, out.buf, out.len) != out.len)
-		die_errno(_("Writing SQUASH_MSG"));
-	if (close(fd))
-		die_errno(_("Finishing SQUASH_MSG"));
+	write_file_buf(git_path_squash_msg(), out.buf, out.len);
 	strbuf_release(&out);
 }
 
 static void finish(struct commit *head_commit,
 		   struct commit_list *remoteheads,
 		   const unsigned char *new_head, const char *msg)
