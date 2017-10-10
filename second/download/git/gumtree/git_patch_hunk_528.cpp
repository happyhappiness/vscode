 
 	if (!active_cache_tree)
 		active_cache_tree = cache_tree();
 
 	if (!cache_tree_fully_valid(active_cache_tree))
 		if (cache_tree_update(&the_index, 0))
-			return error(_("Unable to update cache tree\n"));
+			return error(_("unable to update cache tree\n"));
 
 	return !hashcmp(active_cache_tree->sha1, head_commit->tree->object.oid.hash);
 }
 
 /*
+ * Read the author-script file into an environment block, ready for use in
+ * run_command(), that can be free()d afterwards.
+ */
+static char **read_author_script(void)
+{
+	struct strbuf script = STRBUF_INIT;
+	int i, count = 0;
+	char *p, *p2, **env;
+	size_t env_size;
+
+	if (strbuf_read_file(&script, rebase_path_author_script(), 256) <= 0)
+		return NULL;
+
+	for (p = script.buf; *p; p++)
+		if (skip_prefix(p, "'\\\\''", (const char **)&p2))
+			strbuf_splice(&script, p - script.buf, p2 - p, "'", 1);
+		else if (*p == '\'')
+			strbuf_splice(&script, p-- - script.buf, 1, "", 0);
+		else if (*p == '\n') {
+			*p = '\0';
+			count++;
+		}
+
+	env_size = (count + 1) * sizeof(*env);
+	strbuf_grow(&script, env_size);
+	memmove(script.buf + env_size, script.buf, script.len);
+	p = script.buf + env_size;
+	env = (char **)strbuf_detach(&script, NULL);
+
+	for (i = 0; i < count; i++) {
+		env[i] = p;
+		p += strlen(p) + 1;
+	}
+	env[count] = NULL;
+
+	return env;
+}
+
+static const char staged_changes_advice[] =
+N_("you have staged changes in your working tree\n"
+"If these changes are meant to be squashed into the previous commit, run:\n"
+"\n"
+"  git commit --amend %s\n"
+"\n"
+"If they are meant to go into a new commit, run:\n"
+"\n"
+"  git commit %s\n"
+"\n"
+"In both cases, once you're done, continue with:\n"
+"\n"
+"  git rebase --continue\n");
+
+/*
  * If we are cherry-pick, and if the merge did not result in
  * hand-editing, we will hit this commit and inherit the original
  * author date and name.
+ *
  * If we are revert, or if our cherry-pick results in a hand merge,
  * we had better say that the current user is responsible for that.
+ *
+ * An exception is when run_git_commit() is called during an
+ * interactive rebase: in that case, we will want to retain the
+ * author metadata.
  */
 static int run_git_commit(const char *defmsg, struct replay_opts *opts,
-			  int allow_empty)
+			  int allow_empty, int edit, int amend,
+			  int cleanup_commit_message)
 {
+	char **env = NULL;
 	struct argv_array array;
 	int rc;
 	const char *value;
 
+	if (is_rebase_i(opts)) {
+		env = read_author_script();
+		if (!env) {
+			const char *gpg_opt = gpg_sign_opt_quoted(opts);
+
+			return error(_(staged_changes_advice),
+				     gpg_opt, gpg_opt);
+		}
+	}
+
 	argv_array_init(&array);
 	argv_array_push(&array, "commit");
 	argv_array_push(&array, "-n");
 
+	if (amend)
+		argv_array_push(&array, "--amend");
 	if (opts->gpg_sign)
 		argv_array_pushf(&array, "-S%s", opts->gpg_sign);
 	if (opts->signoff)
 		argv_array_push(&array, "-s");
-	if (!opts->edit) {
-		argv_array_push(&array, "-F");
-		argv_array_push(&array, defmsg);
-		if (!opts->signoff &&
-		    !opts->record_origin &&
-		    git_config_get_value("commit.cleanup", &value))
-			argv_array_push(&array, "--cleanup=verbatim");
-	}
+	if (defmsg)
+		argv_array_pushl(&array, "-F", defmsg, NULL);
+	if (cleanup_commit_message)
+		argv_array_push(&array, "--cleanup=strip");
+	if (edit)
+		argv_array_push(&array, "-e");
+	else if (!cleanup_commit_message &&
+		 !opts->signoff && !opts->record_origin &&
+		 git_config_get_value("commit.cleanup", &value))
+		argv_array_push(&array, "--cleanup=verbatim");
 
 	if (allow_empty)
 		argv_array_push(&array, "--allow-empty");
 
 	if (opts->allow_empty_message)
 		argv_array_push(&array, "--allow-empty-message");
 
-	rc = run_command_v_opt(array.argv, RUN_GIT_CMD);
+	rc = run_command_v_opt_cd_env(array.argv, RUN_GIT_CMD, NULL,
+			(const char *const *)env);
 	argv_array_clear(&array);
+	free(env);
+
 	return rc;
 }
 
 static int is_original_commit_empty(struct commit *commit)
 {
 	const unsigned char *ptree_sha1;
 
 	if (parse_commit(commit))
-		return error(_("Could not parse commit %s\n"),
+		return error(_("could not parse commit %s\n"),
 			     oid_to_hex(&commit->object.oid));
 	if (commit->parents) {
 		struct commit *parent = commit->parents->item;
 		if (parse_commit(parent))
-			return error(_("Could not parse parent commit %s\n"),
+			return error(_("could not parse parent commit %s\n"),
 				oid_to_hex(&parent->object.oid));
 		ptree_sha1 = parent->tree->object.oid.hash;
 	} else {
 		ptree_sha1 = EMPTY_TREE_SHA1_BIN; /* commit is root */
 	}
 
