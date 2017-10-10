 	free(orig_head);
 	free(rebase_amend);
 	free(rebase_orig_head);
 	return split_in_progress;
 }
 
+/*
+ * Turn
+ * "pick d6a2f0303e897ec257dd0e0a39a5ccb709bc2047 some message"
+ * into
+ * "pick d6a2f03 some message"
+ *
+ * The function assumes that the line does not contain useless spaces
+ * before or after the command.
+ */
+static void abbrev_sha1_in_line(struct strbuf *line)
+{
+	struct strbuf **split;
+	int i;
+
+	if (starts_with(line->buf, "exec ") ||
+	    starts_with(line->buf, "x "))
+		return;
+
+	split = strbuf_split_max(line, ' ', 3);
+	if (split[0] && split[1]) {
+		unsigned char sha1[20];
+		const char *abbrev;
+
+		/*
+		 * strbuf_split_max left a space. Trim it and re-add
+		 * it after abbreviation.
+		 */
+		strbuf_trim(split[1]);
+		if (!get_sha1(split[1]->buf, sha1)) {
+			abbrev = find_unique_abbrev(sha1, DEFAULT_ABBREV);
+			strbuf_reset(split[1]);
+			strbuf_addf(split[1], "%s ", abbrev);
+			strbuf_reset(line);
+			for (i = 0; split[i]; i++)
+				strbuf_addf(line, "%s", split[i]->buf);
+		}
+	}
+	for (i = 0; split[i]; i++)
+		strbuf_release(split[i]);
+
+}
+
+static void read_rebase_todolist(const char *fname, struct string_list *lines)
+{
+	struct strbuf line = STRBUF_INIT;
+	FILE *f = fopen(git_path("%s", fname), "r");
+
+	if (!f)
+		die_errno("Could not open file %s for reading",
+			  git_path("%s", fname));
+	while (!strbuf_getline(&line, f, '\n')) {
+		if (line.len && line.buf[0] == comment_line_char)
+			continue;
+		strbuf_trim(&line);
+		if (!line.len)
+			continue;
+		abbrev_sha1_in_line(&line);
+		string_list_append(lines, line.buf);
+	}
+}
+
+static void show_rebase_information(struct wt_status *s,
+					struct wt_status_state *state,
+					const char *color)
+{
+	if (state->rebase_interactive_in_progress) {
+		int i;
+		int nr_lines_to_show = 2;
+
+		struct string_list have_done = STRING_LIST_INIT_DUP;
+		struct string_list yet_to_do = STRING_LIST_INIT_DUP;
+
+		read_rebase_todolist("rebase-merge/done", &have_done);
+		read_rebase_todolist("rebase-merge/git-rebase-todo", &yet_to_do);
+
+		if (have_done.nr == 0)
+			status_printf_ln(s, color, _("No commands done."));
+		else {
+			status_printf_ln(s, color,
+				Q_("Last command done (%d command done):",
+					"Last commands done (%d commands done):",
+					have_done.nr),
+				have_done.nr);
+			for (i = (have_done.nr > nr_lines_to_show)
+				? have_done.nr - nr_lines_to_show : 0;
+				i < have_done.nr;
+				i++)
+				status_printf_ln(s, color, "   %s", have_done.items[i].string);
+			if (have_done.nr > nr_lines_to_show && s->hints)
+				status_printf_ln(s, color,
+					_("  (see more in file %s)"), git_path("rebase-merge/done"));
+		}
+
+		if (yet_to_do.nr == 0)
+			status_printf_ln(s, color,
+					 _("No commands remaining."));
+		else {
+			status_printf_ln(s, color,
+				Q_("Next command to do (%d remaining command):",
+					"Next commands to do (%d remaining commands):",
+					yet_to_do.nr),
+				yet_to_do.nr);
+			for (i = 0; i < nr_lines_to_show && i < yet_to_do.nr; i++)
+				status_printf_ln(s, color, "   %s", yet_to_do.items[i].string);
+			if (s->hints)
+				status_printf_ln(s, color,
+					_("  (use \"git rebase --edit-todo\" to view and edit)"));
+		}
+		string_list_clear(&yet_to_do, 0);
+		string_list_clear(&have_done, 0);
+	}
+}
+
+static void print_rebase_state(struct wt_status *s,
+				struct wt_status_state *state,
+				const char *color)
+{
+	if (state->branch)
+		status_printf_ln(s, color,
+				 _("You are currently rebasing branch '%s' on '%s'."),
+				 state->branch,
+				 state->onto);
+	else
+		status_printf_ln(s, color,
+				 _("You are currently rebasing."));
+}
+
 static void show_rebase_in_progress(struct wt_status *s,
 				struct wt_status_state *state,
 				const char *color)
 {
 	struct stat st;
 
+	show_rebase_information(s, state, color);
 	if (has_unmerged(s)) {
-		if (state->branch)
-			status_printf_ln(s, color,
-					 _("You are currently rebasing branch '%s' on '%s'."),
-					 state->branch,
-					 state->onto);
-		else
-			status_printf_ln(s, color,
-					 _("You are currently rebasing."));
+		print_rebase_state(s, state, color);
 		if (s->hints) {
 			status_printf_ln(s, color,
 				_("  (fix conflicts and then run \"git rebase --continue\")"));
 			status_printf_ln(s, color,
 				_("  (use \"git rebase --skip\" to skip this patch)"));
 			status_printf_ln(s, color,
 				_("  (use \"git rebase --abort\" to check out the original branch)"));
 		}
-	} else if (state->rebase_in_progress || !stat(git_path("MERGE_MSG"), &st)) {
-		if (state->branch)
-			status_printf_ln(s, color,
-					 _("You are currently rebasing branch '%s' on '%s'."),
-					 state->branch,
-					 state->onto);
-		else
-			status_printf_ln(s, color,
-					 _("You are currently rebasing."));
+	} else if (state->rebase_in_progress || !stat(git_path_merge_msg(), &st)) {
+		print_rebase_state(s, state, color);
 		if (s->hints)
 			status_printf_ln(s, color,
 				_("  (all conflicts fixed: run \"git rebase --continue\")"));
 	} else if (split_commit_in_progress(s)) {
 		if (state->branch)
 			status_printf_ln(s, color,
