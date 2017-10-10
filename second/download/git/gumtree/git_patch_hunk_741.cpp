 	if (!empty_commit)
 		return 0;
 	else
 		return 1;
 }
 
+/*
+ * Note that ordering matters in this enum. Not only must it match the mapping
+ * below, it is also divided into several sections that matter.  When adding
+ * new commands, make sure you add it in the right section.
+ */
 enum todo_command {
+	/* commands that handle commits */
 	TODO_PICK = 0,
-	TODO_REVERT
+	TODO_REVERT,
+	TODO_EDIT,
+	TODO_REWORD,
+	TODO_FIXUP,
+	TODO_SQUASH,
+	/* commands that do something else than handling a single commit */
+	TODO_EXEC,
+	/* commands that do nothing but are counted for reporting progress */
+	TODO_NOOP,
+	TODO_DROP,
+	/* comments (not counted for reporting progress) */
+	TODO_COMMENT
 };
 
-static const char *todo_command_strings[] = {
-	"pick",
-	"revert"
+static struct {
+	char c;
+	const char *str;
+} todo_command_info[] = {
+	{ 'p', "pick" },
+	{ 0,   "revert" },
+	{ 'e', "edit" },
+	{ 'r', "reword" },
+	{ 'f', "fixup" },
+	{ 's', "squash" },
+	{ 'x', "exec" },
+	{ 0,   "noop" },
+	{ 'd', "drop" },
+	{ 0,   NULL }
 };
 
 static const char *command_to_string(const enum todo_command command)
 {
-	if ((size_t)command < ARRAY_SIZE(todo_command_strings))
-		return todo_command_strings[command];
+	if (command < TODO_COMMENT)
+		return todo_command_info[command].str;
 	die("Unknown command: %d", command);
 }
 
+static int is_noop(const enum todo_command command)
+{
+	return TODO_NOOP <= command;
+}
+
+static int is_fixup(enum todo_command command)
+{
+	return command == TODO_FIXUP || command == TODO_SQUASH;
+}
+
+static int update_squash_messages(enum todo_command command,
+		struct commit *commit, struct replay_opts *opts)
+{
+	struct strbuf buf = STRBUF_INIT;
+	int count, res;
+	const char *message, *body;
+
+	if (file_exists(rebase_path_squash_msg())) {
+		struct strbuf header = STRBUF_INIT;
+		char *eol, *p;
+
+		if (strbuf_read_file(&buf, rebase_path_squash_msg(), 2048) <= 0)
+			return error(_("could not read '%s'"),
+				rebase_path_squash_msg());
+
+		p = buf.buf + 1;
+		eol = strchrnul(buf.buf, '\n');
+		if (buf.buf[0] != comment_line_char ||
+		    (p += strcspn(p, "0123456789\n")) == eol)
+			return error(_("unexpected 1st line of squash message:"
+				       "\n\n\t%.*s"),
+				     (int)(eol - buf.buf), buf.buf);
+		count = strtol(p, NULL, 10);
+
+		if (count < 1)
+			return error(_("invalid 1st line of squash message:\n"
+				       "\n\t%.*s"),
+				     (int)(eol - buf.buf), buf.buf);
+
+		strbuf_addf(&header, "%c ", comment_line_char);
+		strbuf_addf(&header,
+			    _("This is a combination of %d commits."), ++count);
+		strbuf_splice(&buf, 0, eol - buf.buf, header.buf, header.len);
+		strbuf_release(&header);
+	} else {
+		unsigned char head[20];
+		struct commit *head_commit;
+		const char *head_message, *body;
+
+		if (get_sha1("HEAD", head))
+			return error(_("need a HEAD to fixup"));
+		if (!(head_commit = lookup_commit_reference(head)))
+			return error(_("could not read HEAD"));
+		if (!(head_message = get_commit_buffer(head_commit, NULL)))
+			return error(_("could not read HEAD's commit message"));
+
+		find_commit_subject(head_message, &body);
+		if (write_message(body, strlen(body),
+				  rebase_path_fixup_msg(), 0)) {
+			unuse_commit_buffer(head_commit, head_message);
+			return error(_("cannot write '%s'"),
+				     rebase_path_fixup_msg());
+		}
+
+		count = 2;
+		strbuf_addf(&buf, "%c ", comment_line_char);
+		strbuf_addf(&buf, _("This is a combination of %d commits."),
+			    count);
+		strbuf_addf(&buf, "\n%c ", comment_line_char);
+		strbuf_addstr(&buf, _("This is the 1st commit message:"));
+		strbuf_addstr(&buf, "\n\n");
+		strbuf_addstr(&buf, body);
+
+		unuse_commit_buffer(head_commit, head_message);
+	}
+
+	if (!(message = get_commit_buffer(commit, NULL)))
+		return error(_("could not read commit message of %s"),
+			     oid_to_hex(&commit->object.oid));
+	find_commit_subject(message, &body);
+
+	if (command == TODO_SQUASH) {
+		unlink(rebase_path_fixup_msg());
+		strbuf_addf(&buf, "\n%c ", comment_line_char);
+		strbuf_addf(&buf, _("This is the commit message #%d:"), count);
+		strbuf_addstr(&buf, "\n\n");
+		strbuf_addstr(&buf, body);
+	} else if (command == TODO_FIXUP) {
+		strbuf_addf(&buf, "\n%c ", comment_line_char);
+		strbuf_addf(&buf, _("The commit message #%d will be skipped:"),
+			    count);
+		strbuf_addstr(&buf, "\n\n");
+		strbuf_add_commented_lines(&buf, body, strlen(body));
+	} else
+		return error(_("unknown command: %d"), command);
+	unuse_commit_buffer(commit, message);
+
+	res = write_message(buf.buf, buf.len, rebase_path_squash_msg(), 0);
+	strbuf_release(&buf);
+	return res;
+}
+
+static void flush_rewritten_pending(void) {
+	struct strbuf buf = STRBUF_INIT;
+	unsigned char newsha1[20];
+	FILE *out;
+
+	if (strbuf_read_file(&buf, rebase_path_rewritten_pending(), 82) > 0 &&
+			!get_sha1("HEAD", newsha1) &&
+			(out = fopen(rebase_path_rewritten_list(), "a"))) {
+		char *bol = buf.buf, *eol;
+
+		while (*bol) {
+			eol = strchrnul(bol, '\n');
+			fprintf(out, "%.*s %s\n", (int)(eol - bol),
+					bol, sha1_to_hex(newsha1));
+			if (!*eol)
+				break;
+			bol = eol + 1;
+		}
+		fclose(out);
+		unlink(rebase_path_rewritten_pending());
+	}
+	strbuf_release(&buf);
+}
+
+static void record_in_rewritten(struct object_id *oid,
+		enum todo_command next_command) {
+	FILE *out = fopen(rebase_path_rewritten_pending(), "a");
+
+	if (!out)
+		return;
+
+	fprintf(out, "%s\n", oid_to_hex(oid));
+	fclose(out);
+
+	if (!is_fixup(next_command))
+		flush_rewritten_pending();
+}
 
 static int do_pick_commit(enum todo_command command, struct commit *commit,
-		struct replay_opts *opts)
+		struct replay_opts *opts, int final_fixup)
 {
+	int edit = opts->edit, cleanup_commit_message = 0;
+	const char *msg_file = edit ? NULL : git_path_merge_msg();
 	unsigned char head[20];
 	struct commit *base, *next, *parent;
 	const char *base_label, *next_label;
 	struct commit_message msg = { NULL, NULL, NULL, NULL };
 	struct strbuf msgbuf = STRBUF_INIT;
-	int res, unborn = 0, allow;
+	int res, unborn = 0, amend = 0, allow = 0;
 
 	if (opts->no_commit) {
 		/*
 		 * We do not intend to commit immediately.  We just want to
 		 * merge the differences in, so let's compute the tree
 		 * that represents the "current" state for merge-recursive
