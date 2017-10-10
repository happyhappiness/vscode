 {
 	struct combine_diff_path *path = (struct combine_diff_path *)obj;
 
 	return path->path;
 }
 
+
+/* find set of paths that every parent touches */
+static struct combine_diff_path *find_paths_generic(const unsigned char *sha1,
+	const struct sha1_array *parents, struct diff_options *opt)
+{
+	struct combine_diff_path *paths = NULL;
+	int i, num_parent = parents->nr;
+
+	int output_format = opt->output_format;
+	const char *orderfile = opt->orderfile;
+
+	opt->output_format = DIFF_FORMAT_NO_OUTPUT;
+	/* tell diff_tree to emit paths in sorted (=tree) order */
+	opt->orderfile = NULL;
+
+	/* D(A,P1...Pn) = D(A,P1) ^ ... ^ D(A,Pn)  (wrt paths) */
+	for (i = 0; i < num_parent; i++) {
+		/*
+		 * show stat against the first parent even when doing
+		 * combined diff.
+		 */
+		int stat_opt = (output_format &
+				(DIFF_FORMAT_NUMSTAT|DIFF_FORMAT_DIFFSTAT));
+		if (i == 0 && stat_opt)
+			opt->output_format = stat_opt;
+		else
+			opt->output_format = DIFF_FORMAT_NO_OUTPUT;
+		diff_tree_sha1(parents->sha1[i], sha1, "", opt);
+		diffcore_std(opt);
+		paths = intersect_paths(paths, i, num_parent);
+
+		/* if showing diff, show it in requested order */
+		if (opt->output_format != DIFF_FORMAT_NO_OUTPUT &&
+		    orderfile) {
+			diffcore_order(orderfile);
+		}
+
+		diff_flush(opt);
+	}
+
+	opt->output_format = output_format;
+	opt->orderfile = orderfile;
+	return paths;
+}
+
+
+/*
+ * find set of paths that everybody touches, assuming diff is run without
+ * rename/copy detection, etc, comparing all trees simultaneously (= faster).
+ */
+static struct combine_diff_path *find_paths_multitree(
+	const unsigned char *sha1, const struct sha1_array *parents,
+	struct diff_options *opt)
+{
+	int i, nparent = parents->nr;
+	const unsigned char **parents_sha1;
+	struct combine_diff_path paths_head;
+	struct strbuf base;
+
+	parents_sha1 = xmalloc(nparent * sizeof(parents_sha1[0]));
+	for (i = 0; i < nparent; i++)
+		parents_sha1[i] = parents->sha1[i];
+
+	/* fake list head, so worker can assume it is non-NULL */
+	paths_head.next = NULL;
+
+	strbuf_init(&base, PATH_MAX);
+	diff_tree_paths(&paths_head, sha1, parents_sha1, nparent, &base, opt);
+
+	strbuf_release(&base);
+	free(parents_sha1);
+	return paths_head.next;
+}
+
+
 void diff_tree_combined(const unsigned char *sha1,
 			const struct sha1_array *parents,
 			int dense,
 			struct rev_info *rev)
 {
 	struct diff_options *opt = &rev->diffopt;
 	struct diff_options diffopts;
-	struct combine_diff_path *p, *paths = NULL;
+	struct combine_diff_path *p, *paths;
 	int i, num_paths, needsep, show_log_first, num_parent = parents->nr;
+	int need_generic_pathscan;
+
+	/* nothing to do, if no parents */
+	if (!num_parent)
+		return;
+
+	show_log_first = !!rev->loginfo && !rev->no_commit_id;
+	needsep = 0;
+	if (show_log_first) {
+		show_log(rev);
+
+		if (rev->verbose_header && opt->output_format &&
+		    opt->output_format != DIFF_FORMAT_NO_OUTPUT)
+			printf("%s%c", diff_line_prefix(opt),
+			       opt->line_termination);
+	}
 
 	diffopts = *opt;
 	copy_pathspec(&diffopts.pathspec, &opt->pathspec);
-	diffopts.output_format = DIFF_FORMAT_NO_OUTPUT;
 	DIFF_OPT_SET(&diffopts, RECURSIVE);
 	DIFF_OPT_CLR(&diffopts, ALLOW_EXTERNAL);
-	/* tell diff_tree to emit paths in sorted (=tree) order */
-	diffopts.orderfile = NULL;
 
-	show_log_first = !!rev->loginfo && !rev->no_commit_id;
-	needsep = 0;
-	/* find set of paths that everybody touches */
-	for (i = 0; i < num_parent; i++) {
-		/* show stat against the first parent even
+	/* find set of paths that everybody touches
+	 *
+	 * NOTE
+	 *
+	 * Diffcore transformations are bound to diff_filespec and logic
+	 * comparing two entries - i.e. they do not apply directly to combine
+	 * diff.
+	 *
+	 * If some of such transformations is requested - we launch generic
+	 * path scanning, which works significantly slower compared to
+	 * simultaneous all-trees-in-one-go scan in find_paths_multitree().
+	 *
+	 * TODO some of the filters could be ported to work on
+	 * combine_diff_paths - i.e. all functionality that skips paths, so in
+	 * theory, we could end up having only multitree path scanning.
+	 *
+	 * NOTE please keep this semantically in sync with diffcore_std()
+	 */
+	need_generic_pathscan = opt->skip_stat_unmatch	||
+			DIFF_OPT_TST(opt, FOLLOW_RENAMES)	||
+			opt->break_opt != -1	||
+			opt->detect_rename	||
+			opt->pickaxe		||
+			opt->filter;
+
+
+	if (need_generic_pathscan) {
+		/*
+		 * NOTE generic case also handles --stat, as it computes
+		 * diff(sha1,parent_i) for all i to do the job, specifically
+		 * for parent0.
+		 */
+		paths = find_paths_generic(sha1, parents, &diffopts);
+	}
+	else {
+		int stat_opt;
+		paths = find_paths_multitree(sha1, parents, &diffopts);
+
+		/*
+		 * show stat against the first parent even
 		 * when doing combined diff.
 		 */
-		int stat_opt = (opt->output_format &
+		stat_opt = (opt->output_format &
 				(DIFF_FORMAT_NUMSTAT|DIFF_FORMAT_DIFFSTAT));
-		if (i == 0 && stat_opt)
+		if (stat_opt) {
 			diffopts.output_format = stat_opt;
-		else
-			diffopts.output_format = DIFF_FORMAT_NO_OUTPUT;
-		diff_tree_sha1(parents->sha1[i], sha1, "", &diffopts);
-		diffcore_std(&diffopts);
-		paths = intersect_paths(paths, i, num_parent);
 
-		if (show_log_first && i == 0) {
-			show_log(rev);
-
-			if (rev->verbose_header && opt->output_format &&
-			    opt->output_format != DIFF_FORMAT_NO_OUTPUT)
-				printf("%s%c", diff_line_prefix(opt),
-				       opt->line_termination);
+			diff_tree_sha1(parents->sha1[0], sha1, "", &diffopts);
+			diffcore_std(&diffopts);
+			if (opt->orderfile)
+				diffcore_order(opt->orderfile);
+			diff_flush(&diffopts);
 		}
-
-		/* if showing diff, show it in requested order */
-		if (diffopts.output_format != DIFF_FORMAT_NO_OUTPUT &&
-		    opt->orderfile) {
-			diffcore_order(opt->orderfile);
-		}
-
-		diff_flush(&diffopts);
 	}
 
 	/* find out number of surviving paths */
 	for (num_paths = 0, p = paths; p; p = p->next)
 		num_paths++;
 
