 		isatty(0) && isatty(1) &&
 		st_stdin.st_dev == st_stdout.st_dev &&
 		st_stdin.st_ino == st_stdout.st_ino &&
 		st_stdin.st_mode == st_stdout.st_mode);
 }
 
-static struct commit_list *collect_parents(struct commit *head_commit,
-					   int *head_subsumed,
-					   int argc, const char **argv)
+static struct commit_list *reduce_parents(struct commit *head_commit,
+					  int *head_subsumed,
+					  struct commit_list *remoteheads)
 {
-	int i;
-	struct commit_list *remoteheads = NULL, *parents, *next;
-	struct commit_list **remotes = &remoteheads;
+	struct commit_list *parents, *next, **remotes = &remoteheads;
 
-	if (head_commit)
-		remotes = &commit_list_insert(head_commit, remotes)->next;
-	for (i = 0; i < argc; i++) {
-		struct commit *commit = get_merge_parent(argv[i]);
-		if (!commit)
-			help_unknown_ref(argv[i], "merge",
-					 "not something we can merge");
-		remotes = &commit_list_insert(commit, remotes)->next;
-	}
-	*remotes = NULL;
+	/*
+	 * Is the current HEAD reachable from another commit being
+	 * merged?  If so we do not want to record it as a parent of
+	 * the resulting merge, unless --no-ff is given.  We will flip
+	 * this variable to 0 when we find HEAD among the independent
+	 * tips being merged.
+	 */
+	*head_subsumed = 1;
 
+	/* Find what parents to record by checking independent ones. */
 	parents = reduce_heads(remoteheads);
 
-	*head_subsumed = 1; /* we will flip this to 0 when we find it */
 	for (remoteheads = NULL, remotes = &remoteheads;
 	     parents;
 	     parents = next) {
 		struct commit *commit = parents->item;
 		next = parents->next;
 		if (commit == head_commit)
 			*head_subsumed = 0;
 		else
 			remotes = &commit_list_insert(commit, remotes)->next;
+		free(parents);
+	}
+	return remoteheads;
+}
+
+static void prepare_merge_message(struct strbuf *merge_names, struct strbuf *merge_msg)
+{
+	struct fmt_merge_msg_opts opts;
+
+	memset(&opts, 0, sizeof(opts));
+	opts.add_title = !have_message;
+	opts.shortlog_len = shortlog_len;
+	opts.credit_people = (0 < option_edit);
+
+	fmt_merge_msg(merge_names, merge_msg, &opts);
+	if (merge_msg->len)
+		strbuf_setlen(merge_msg, merge_msg->len - 1);
+}
+
+static void handle_fetch_head(struct commit_list **remotes, struct strbuf *merge_names)
+{
+	const char *filename;
+	int fd, pos, npos;
+	struct strbuf fetch_head_file = STRBUF_INIT;
+
+	if (!merge_names)
+		merge_names = &fetch_head_file;
+
+	filename = git_path("FETCH_HEAD");
+	fd = open(filename, O_RDONLY);
+	if (fd < 0)
+		die_errno(_("could not open '%s' for reading"), filename);
+
+	if (strbuf_read(merge_names, fd, 0) < 0)
+		die_errno(_("could not read '%s'"), filename);
+	if (close(fd) < 0)
+		die_errno(_("could not close '%s'"), filename);
+
+	for (pos = 0; pos < merge_names->len; pos = npos) {
+		unsigned char sha1[20];
+		char *ptr;
+		struct commit *commit;
+
+		ptr = strchr(merge_names->buf + pos, '\n');
+		if (ptr)
+			npos = ptr - merge_names->buf + 1;
+		else
+			npos = merge_names->len;
+
+		if (npos - pos < 40 + 2 ||
+		    get_sha1_hex(merge_names->buf + pos, sha1))
+			commit = NULL; /* bad */
+		else if (memcmp(merge_names->buf + pos + 40, "\t\t", 2))
+			continue; /* not-for-merge */
+		else {
+			char saved = merge_names->buf[pos + 40];
+			merge_names->buf[pos + 40] = '\0';
+			commit = get_merge_parent(merge_names->buf + pos);
+			merge_names->buf[pos + 40] = saved;
+		}
+		if (!commit) {
+			if (ptr)
+				*ptr = '\0';
+			die("not something we can merge in %s: %s",
+			    filename, merge_names->buf + pos);
+		}
+		remotes = &commit_list_insert(commit, remotes)->next;
+	}
+
+	if (merge_names == &fetch_head_file)
+		strbuf_release(&fetch_head_file);
+}
+
+static struct commit_list *collect_parents(struct commit *head_commit,
+					   int *head_subsumed,
+					   int argc, const char **argv,
+					   struct strbuf *merge_msg)
+{
+	int i;
+	struct commit_list *remoteheads = NULL;
+	struct commit_list **remotes = &remoteheads;
+	struct strbuf merge_names = STRBUF_INIT, *autogen = NULL;
+
+	if (merge_msg && (!have_message || shortlog_len))
+		autogen = &merge_names;
+
+	if (head_commit)
+		remotes = &commit_list_insert(head_commit, remotes)->next;
+
+	if (argc == 1 && !strcmp(argv[0], "FETCH_HEAD")) {
+		handle_fetch_head(remotes, autogen);
+		remoteheads = reduce_parents(head_commit, head_subsumed, remoteheads);
+	} else {
+		for (i = 0; i < argc; i++) {
+			struct commit *commit = get_merge_parent(argv[i]);
+			if (!commit)
+				help_unknown_ref(argv[i], "merge",
+						 "not something we can merge");
+			remotes = &commit_list_insert(commit, remotes)->next;
+		}
+		remoteheads = reduce_parents(head_commit, head_subsumed, remoteheads);
+		if (autogen) {
+			struct commit_list *p;
+			for (p = remoteheads; p; p = p->next)
+				merge_name(merge_remote_util(p->item)->name, autogen);
+		}
+	}
+
+	if (autogen) {
+		prepare_merge_message(autogen, merge_msg);
+		strbuf_release(autogen);
 	}
+
 	return remoteheads;
 }
 
 int cmd_merge(int argc, const char **argv, const char *prefix)
 {
 	unsigned char result_tree[20];
