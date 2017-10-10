  *
  * Will always return 0 as the patch should never be skipped.
  */
 static int parse_mail_rebase(struct am_state *state, const char *mail)
 {
 	struct commit *commit;
-	unsigned char commit_sha1[GIT_SHA1_RAWSZ];
+	struct object_id commit_oid;
 
-	if (get_mail_commit_sha1(commit_sha1, mail) < 0)
+	if (get_mail_commit_oid(&commit_oid, mail) < 0)
 		die(_("could not parse %s"), mail);
 
-	commit = lookup_commit_or_die(commit_sha1, mail);
+	commit = lookup_commit_or_die(commit_oid.hash, mail);
 
 	get_commit_info(state, commit);
 
 	write_commit_patch(state, commit);
 
-	hashcpy(state->orig_commit, commit_sha1);
-	write_state_text(state, "original-commit", sha1_to_hex(commit_sha1));
+	oidcpy(&state->orig_commit, &commit_oid);
+	write_state_text(state, "original-commit", oid_to_hex(&commit_oid));
 
 	return 0;
 }
 
 /**
  * Applies current patch with git-apply. Returns 0 on success, -1 otherwise. If
  * `index_file` is not NULL, the patch will be applied to that index.
  */
 static int run_apply(const struct am_state *state, const char *index_file)
 {
-	struct child_process cp = CHILD_PROCESS_INIT;
-
-	cp.git_cmd = 1;
-
-	if (index_file)
-		argv_array_pushf(&cp.env_array, "GIT_INDEX_FILE=%s", index_file);
+	struct argv_array apply_paths = ARGV_ARRAY_INIT;
+	struct argv_array apply_opts = ARGV_ARRAY_INIT;
+	struct apply_state apply_state;
+	int res, opts_left;
+	static struct lock_file lock_file;
+	int force_apply = 0;
+	int options = 0;
+
+	if (init_apply_state(&apply_state, NULL, &lock_file))
+		die("BUG: init_apply_state() failed");
+
+	argv_array_push(&apply_opts, "apply");
+	argv_array_pushv(&apply_opts, state->git_apply_opts.argv);
+
+	opts_left = apply_parse_options(apply_opts.argc, apply_opts.argv,
+					&apply_state, &force_apply, &options,
+					NULL);
+
+	if (opts_left != 0)
+		die("unknown option passed through to git apply");
+
+	if (index_file) {
+		apply_state.index_file = index_file;
+		apply_state.cached = 1;
+	} else
+		apply_state.check_index = 1;
 
 	/*
 	 * If we are allowed to fall back on 3-way merge, don't give false
 	 * errors during the initial attempt.
 	 */
-	if (state->threeway && !index_file) {
-		cp.no_stdout = 1;
-		cp.no_stderr = 1;
-	}
+	if (state->threeway && !index_file)
+		apply_state.apply_verbosity = verbosity_silent;
 
-	argv_array_push(&cp.args, "apply");
+	if (check_apply_state(&apply_state, force_apply))
+		die("BUG: check_apply_state() failed");
 
-	argv_array_pushv(&cp.args, state->git_apply_opts.argv);
+	argv_array_push(&apply_paths, am_path(state, "patch"));
 
-	if (index_file)
-		argv_array_push(&cp.args, "--cached");
-	else
-		argv_array_push(&cp.args, "--index");
+	res = apply_all_patches(&apply_state, apply_paths.argc, apply_paths.argv, options);
 
-	argv_array_push(&cp.args, am_path(state, "patch"));
+	argv_array_clear(&apply_paths);
+	argv_array_clear(&apply_opts);
+	clear_apply_state(&apply_state);
 
-	if (run_command(&cp))
-		return -1;
+	if (res)
+		return res;
 
-	/* Reload index as git-apply will have modified it. */
-	discard_cache();
-	read_cache_from(index_file ? index_file : get_index_file());
+	if (index_file) {
+		/* Reload index as apply_all_patches() will have modified it. */
+		discard_cache();
+		read_cache_from(index_file);
+	}
 
 	return 0;
 }
 
 /**
  * Builds an index that contains just the blobs needed for a 3way merge.
