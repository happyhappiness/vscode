 			advise(_("after resolving the conflicts, mark the corrected paths\n"
 				 "with 'git add <paths>' or 'git rm <paths>'\n"
 				 "and commit the result with 'git commit'"));
 	}
 }
 
-static void write_message(struct strbuf *msgbuf, const char *filename)
+static int write_message(const void *buf, size_t len, const char *filename,
+			 int append_eol)
 {
 	static struct lock_file msg_file;
 
-	int msg_fd = hold_lock_file_for_update(&msg_file, filename,
-					       LOCK_DIE_ON_ERROR);
-	if (write_in_full(msg_fd, msgbuf->buf, msgbuf->len) < 0)
-		die_errno(_("Could not write to %s"), filename);
-	strbuf_release(msgbuf);
-	if (commit_lock_file(&msg_file) < 0)
-		die(_("Error wrapping up %s."), filename);
+	int msg_fd = hold_lock_file_for_update(&msg_file, filename, 0);
+	if (msg_fd < 0)
+		return error_errno(_("could not lock '%s'"), filename);
+	if (write_in_full(msg_fd, buf, len) < 0) {
+		rollback_lock_file(&msg_file);
+		return error_errno(_("could not write to '%s'"), filename);
+	}
+	if (append_eol && write(msg_fd, "\n", 1) < 0) {
+		rollback_lock_file(&msg_file);
+		return error_errno(_("could not write eol to '%s'"), filename);
+	}
+	if (commit_lock_file(&msg_file) < 0) {
+		rollback_lock_file(&msg_file);
+		return error(_("failed to finalize '%s'."), filename);
+	}
+
+	return 0;
+}
+
+/*
+ * Reads a file that was presumably written by a shell script, i.e. with an
+ * end-of-line marker that needs to be stripped.
+ *
+ * Note that only the last end-of-line marker is stripped, consistent with the
+ * behavior of "$(cat path)" in a shell script.
+ *
+ * Returns 1 if the file was read, 0 if it could not be read or does not exist.
+ */
+static int read_oneliner(struct strbuf *buf,
+	const char *path, int skip_if_empty)
+{
+	int orig_len = buf->len;
+
+	if (!file_exists(path))
+		return 0;
+
+	if (strbuf_read_file(buf, path, 0) < 0) {
+		warning_errno(_("could not read '%s'"), path);
+		return 0;
+	}
+
+	if (buf->len > orig_len && buf->buf[buf->len - 1] == '\n') {
+		if (--buf->len > orig_len && buf->buf[buf->len - 1] == '\r')
+			--buf->len;
+		buf->buf[buf->len] = '\0';
+	}
+
+	if (skip_if_empty && buf->len == orig_len)
+		return 0;
+
+	return 1;
 }
 
 static struct tree *empty_tree(void)
 {
 	return lookup_tree(EMPTY_TREE_SHA1_BIN);
 }
 
 static int error_dirty_index(struct replay_opts *opts)
 {
 	if (read_cache_unmerged())
-		return error_resolve_conflict(action_name(opts));
+		return error_resolve_conflict(_(action_name(opts)));
 
-	/* Different translation strings for cherry-pick and revert */
-	if (opts->action == REPLAY_PICK)
-		error(_("Your local changes would be overwritten by cherry-pick."));
-	else
-		error(_("Your local changes would be overwritten by revert."));
+	error(_("your local changes would be overwritten by %s."),
+		_(action_name(opts)));
 
 	if (advice_commit_before_merge)
-		advise(_("Commit your changes or stash them to proceed."));
+		advise(_("commit your changes or stash them to proceed."));
 	return -1;
 }
 
 static int fast_forward_to(const unsigned char *to, const unsigned char *from,
 			int unborn, struct replay_opts *opts)
 {
 	struct ref_transaction *transaction;
 	struct strbuf sb = STRBUF_INIT;
 	struct strbuf err = STRBUF_INIT;
 
 	read_cache();
 	if (checkout_fast_forward(from, to, 1))
-		exit(128); /* the callee should have complained already */
+		return -1; /* the callee should have complained already */
 
-	strbuf_addf(&sb, _("%s: fast-forward"), action_name(opts));
+	strbuf_addf(&sb, _("%s: fast-forward"), _(action_name(opts)));
 
 	transaction = ref_transaction_begin(&err);
 	if (!transaction ||
 	    ref_transaction_update(transaction, "HEAD",
 				   to, unborn ? null_sha1 : from,
 				   0, sb.buf, &err) ||
