 		strbuf_addch(&sb, '\n');
 		fprintf(f, "%s", sb.buf);
 	}
 	strbuf_release(&sb);
 }
 
-void show_submodule_summary(FILE *f, const char *path,
+/* Helper function to display the submodule header line prior to the full
+ * summary output. If it can locate the submodule objects directory it will
+ * attempt to lookup both the left and right commits and put them into the
+ * left and right pointers.
+ */
+static void show_submodule_header(FILE *f, const char *path,
 		const char *line_prefix,
-		unsigned char one[20], unsigned char two[20],
+		struct object_id *one, struct object_id *two,
 		unsigned dirty_submodule, const char *meta,
-		const char *del, const char *add, const char *reset)
+		const char *reset,
+		struct commit **left, struct commit **right,
+		struct commit_list **merge_bases)
 {
-	struct rev_info rev;
-	struct commit *left = NULL, *right = NULL;
 	const char *message = NULL;
 	struct strbuf sb = STRBUF_INIT;
 	int fast_forward = 0, fast_backward = 0;
 
-	if (is_null_sha1(two))
-		message = "(submodule deleted)";
-	else if (add_submodule_odb(path))
-		message = "(not checked out)";
-	else if (is_null_sha1(one))
-		message = "(new submodule)";
-	else if (!(left = lookup_commit_reference(one)) ||
-		 !(right = lookup_commit_reference(two)))
-		message = "(commits not present)";
-	else if (prepare_submodule_summary(&rev, path, left, right,
-					   &fast_forward, &fast_backward))
-		message = "(revision walker failed)";
-
 	if (dirty_submodule & DIRTY_SUBMODULE_UNTRACKED)
 		fprintf(f, "%sSubmodule %s contains untracked content\n",
 			line_prefix, path);
 	if (dirty_submodule & DIRTY_SUBMODULE_MODIFIED)
 		fprintf(f, "%sSubmodule %s contains modified content\n",
 			line_prefix, path);
 
-	if (!hashcmp(one, two)) {
+	if (is_null_oid(one))
+		message = "(new submodule)";
+	else if (is_null_oid(two))
+		message = "(submodule deleted)";
+
+	if (add_submodule_odb(path)) {
+		if (!message)
+			message = "(not initialized)";
+		goto output_header;
+	}
+
+	/*
+	 * Attempt to lookup the commit references, and determine if this is
+	 * a fast forward or fast backwards update.
+	 */
+	*left = lookup_commit_reference(one->hash);
+	*right = lookup_commit_reference(two->hash);
+
+	/*
+	 * Warn about missing commits in the submodule project, but only if
+	 * they aren't null.
+	 */
+	if ((!is_null_oid(one) && !*left) ||
+	     (!is_null_oid(two) && !*right))
+		message = "(commits not present)";
+
+	*merge_bases = get_merge_bases(*left, *right);
+	if (*merge_bases) {
+		if ((*merge_bases)->item == *left)
+			fast_forward = 1;
+		else if ((*merge_bases)->item == *right)
+			fast_backward = 1;
+	}
+
+	if (!oidcmp(one, two)) {
 		strbuf_release(&sb);
 		return;
 	}
 
+output_header:
 	strbuf_addf(&sb, "%s%sSubmodule %s ", line_prefix, meta, path);
-	strbuf_add_unique_abbrev(&sb, one, DEFAULT_ABBREV);
+	strbuf_add_unique_abbrev(&sb, one->hash, DEFAULT_ABBREV);
 	strbuf_addstr(&sb, (fast_backward || fast_forward) ? ".." : "...");
-	strbuf_add_unique_abbrev(&sb, two, DEFAULT_ABBREV);
+	strbuf_add_unique_abbrev(&sb, two->hash, DEFAULT_ABBREV);
 	if (message)
 		strbuf_addf(&sb, " %s%s\n", message, reset);
 	else
 		strbuf_addf(&sb, "%s:%s\n", fast_backward ? " (rewind)" : "", reset);
 	fwrite(sb.buf, sb.len, 1, f);
 
-	if (!message) /* only NULL if we succeeded in setting up the walk */
-		print_submodule_summary(&rev, f, line_prefix, del, add, reset);
+	strbuf_release(&sb);
+}
+
+void show_submodule_summary(FILE *f, const char *path,
+		const char *line_prefix,
+		struct object_id *one, struct object_id *two,
+		unsigned dirty_submodule, const char *meta,
+		const char *del, const char *add, const char *reset)
+{
+	struct rev_info rev;
+	struct commit *left = NULL, *right = NULL;
+	struct commit_list *merge_bases = NULL;
+
+	show_submodule_header(f, path, line_prefix, one, two, dirty_submodule,
+			      meta, reset, &left, &right, &merge_bases);
+
+	/*
+	 * If we don't have both a left and a right pointer, there is no
+	 * reason to try and display a summary. The header line should contain
+	 * all the information the user needs.
+	 */
+	if (!left || !right)
+		goto out;
+
+	/* Treat revision walker failure the same as missing commits */
+	if (prepare_submodule_summary(&rev, path, left, right, merge_bases)) {
+		fprintf(f, "%s(revision walker failed)\n", line_prefix);
+		goto out;
+	}
+
+	print_submodule_summary(&rev, f, line_prefix, del, add, reset);
+
+out:
+	if (merge_bases)
+		free_commit_list(merge_bases);
+	clear_commit_marks(left, ~0);
+	clear_commit_marks(right, ~0);
+}
+
+void show_submodule_inline_diff(FILE *f, const char *path,
+		const char *line_prefix,
+		struct object_id *one, struct object_id *two,
+		unsigned dirty_submodule, const char *meta,
+		const char *del, const char *add, const char *reset,
+		const struct diff_options *o)
+{
+	const struct object_id *old = &empty_tree_oid, *new = &empty_tree_oid;
+	struct commit *left = NULL, *right = NULL;
+	struct commit_list *merge_bases = NULL;
+	struct strbuf submodule_dir = STRBUF_INIT;
+	struct child_process cp = CHILD_PROCESS_INIT;
+
+	show_submodule_header(f, path, line_prefix, one, two, dirty_submodule,
+			      meta, reset, &left, &right, &merge_bases);
+
+	/* We need a valid left and right commit to display a difference */
+	if (!(left || is_null_oid(one)) ||
+	    !(right || is_null_oid(two)))
+		goto done;
+
+	if (left)
+		old = one;
+	if (right)
+		new = two;
+
+	fflush(f);
+	cp.git_cmd = 1;
+	cp.dir = path;
+	cp.out = dup(fileno(f));
+	cp.no_stdin = 1;
+
+	/* TODO: other options may need to be passed here. */
+	argv_array_push(&cp.args, "diff");
+	argv_array_pushf(&cp.args, "--line-prefix=%s", line_prefix);
+	if (DIFF_OPT_TST(o, REVERSE_DIFF)) {
+		argv_array_pushf(&cp.args, "--src-prefix=%s%s/",
+				 o->b_prefix, path);
+		argv_array_pushf(&cp.args, "--dst-prefix=%s%s/",
+				 o->a_prefix, path);
+	} else {
+		argv_array_pushf(&cp.args, "--src-prefix=%s%s/",
+				 o->a_prefix, path);
+		argv_array_pushf(&cp.args, "--dst-prefix=%s%s/",
+				 o->b_prefix, path);
+	}
+	argv_array_push(&cp.args, oid_to_hex(old));
+	/*
+	 * If the submodule has modified content, we will diff against the
+	 * work tree, under the assumption that the user has asked for the
+	 * diff format and wishes to actually see all differences even if they
+	 * haven't yet been committed to the submodule yet.
+	 */
+	if (!(dirty_submodule & DIRTY_SUBMODULE_MODIFIED))
+		argv_array_push(&cp.args, oid_to_hex(new));
+
+	if (run_command(&cp))
+		fprintf(f, "(diff failed)\n");
+
+done:
+	strbuf_release(&submodule_dir);
+	if (merge_bases)
+		free_commit_list(merge_bases);
 	if (left)
 		clear_commit_marks(left, ~0);
 	if (right)
 		clear_commit_marks(right, ~0);
-
-	strbuf_release(&sb);
 }
 
 void set_config_fetch_recurse_submodules(int value)
 {
 	config_fetch_recurse_submodules = value;
 }
