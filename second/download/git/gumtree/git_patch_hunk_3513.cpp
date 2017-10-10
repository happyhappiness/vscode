 					: "commit";
 		pptr = &commit_list_insert(current_head, pptr)->next;
 	}
 
 	/* Finally, get the commit message */
 	strbuf_reset(&sb);
-	if (strbuf_read_file(&sb, git_path(commit_editmsg), 0) < 0) {
+	if (strbuf_read_file(&sb, git_path_commit_editmsg(), 0) < 0) {
 		int saved_errno = errno;
 		rollback_index_files();
 		die(_("could not read commit message: %s"), strerror(saved_errno));
 	}
 
 	if (verbose || /* Truncate the message just before the diff, if any. */
