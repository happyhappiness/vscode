 
 	status = run_command(&child);
 	if (status)
 		exit(status);
 }
 
-static int grep_cache(struct grep_opt *opt, const struct pathspec *pathspec, int cached)
+static void compile_submodule_options(const struct grep_opt *opt,
+				      const struct pathspec *pathspec,
+				      int cached, int untracked,
+				      int opt_exclude, int use_index,
+				      int pattern_type_arg)
+{
+	struct grep_pat *pattern;
+	int i;
+
+	if (recurse_submodules)
+		argv_array_push(&submodule_options, "--recurse-submodules");
+
+	if (cached)
+		argv_array_push(&submodule_options, "--cached");
+	if (!use_index)
+		argv_array_push(&submodule_options, "--no-index");
+	if (untracked)
+		argv_array_push(&submodule_options, "--untracked");
+	if (opt_exclude > 0)
+		argv_array_push(&submodule_options, "--exclude-standard");
+
+	if (opt->invert)
+		argv_array_push(&submodule_options, "-v");
+	if (opt->ignore_case)
+		argv_array_push(&submodule_options, "-i");
+	if (opt->word_regexp)
+		argv_array_push(&submodule_options, "-w");
+	switch (opt->binary) {
+	case GREP_BINARY_NOMATCH:
+		argv_array_push(&submodule_options, "-I");
+		break;
+	case GREP_BINARY_TEXT:
+		argv_array_push(&submodule_options, "-a");
+		break;
+	default:
+		break;
+	}
+	if (opt->allow_textconv)
+		argv_array_push(&submodule_options, "--textconv");
+	if (opt->max_depth != -1)
+		argv_array_pushf(&submodule_options, "--max-depth=%d",
+				 opt->max_depth);
+	if (opt->linenum)
+		argv_array_push(&submodule_options, "-n");
+	if (!opt->pathname)
+		argv_array_push(&submodule_options, "-h");
+	if (!opt->relative)
+		argv_array_push(&submodule_options, "--full-name");
+	if (opt->name_only)
+		argv_array_push(&submodule_options, "-l");
+	if (opt->unmatch_name_only)
+		argv_array_push(&submodule_options, "-L");
+	if (opt->null_following_name)
+		argv_array_push(&submodule_options, "-z");
+	if (opt->count)
+		argv_array_push(&submodule_options, "-c");
+	if (opt->file_break)
+		argv_array_push(&submodule_options, "--break");
+	if (opt->heading)
+		argv_array_push(&submodule_options, "--heading");
+	if (opt->pre_context)
+		argv_array_pushf(&submodule_options, "--before-context=%d",
+				 opt->pre_context);
+	if (opt->post_context)
+		argv_array_pushf(&submodule_options, "--after-context=%d",
+				 opt->post_context);
+	if (opt->funcname)
+		argv_array_push(&submodule_options, "-p");
+	if (opt->funcbody)
+		argv_array_push(&submodule_options, "-W");
+	if (opt->all_match)
+		argv_array_push(&submodule_options, "--all-match");
+	if (opt->debug)
+		argv_array_push(&submodule_options, "--debug");
+	if (opt->status_only)
+		argv_array_push(&submodule_options, "-q");
+
+	switch (pattern_type_arg) {
+	case GREP_PATTERN_TYPE_BRE:
+		argv_array_push(&submodule_options, "-G");
+		break;
+	case GREP_PATTERN_TYPE_ERE:
+		argv_array_push(&submodule_options, "-E");
+		break;
+	case GREP_PATTERN_TYPE_FIXED:
+		argv_array_push(&submodule_options, "-F");
+		break;
+	case GREP_PATTERN_TYPE_PCRE:
+		argv_array_push(&submodule_options, "-P");
+		break;
+	case GREP_PATTERN_TYPE_UNSPECIFIED:
+		break;
+	}
+
+	for (pattern = opt->pattern_list; pattern != NULL;
+	     pattern = pattern->next) {
+		switch (pattern->token) {
+		case GREP_PATTERN:
+			argv_array_pushf(&submodule_options, "-e%s",
+					 pattern->pattern);
+			break;
+		case GREP_AND:
+		case GREP_OPEN_PAREN:
+		case GREP_CLOSE_PAREN:
+		case GREP_NOT:
+		case GREP_OR:
+			argv_array_push(&submodule_options, pattern->pattern);
+			break;
+		/* BODY and HEAD are not used by git-grep */
+		case GREP_PATTERN_BODY:
+		case GREP_PATTERN_HEAD:
+			break;
+		}
+	}
+
+	/*
+	 * Limit number of threads for child process to use.
+	 * This is to prevent potential fork-bomb behavior of git-grep as each
+	 * submodule process has its own thread pool.
+	 */
+	argv_array_pushf(&submodule_options, "--threads=%d",
+			 (num_threads + 1) / 2);
+
+	/* Add Pathspecs */
+	argv_array_push(&submodule_options, "--");
+	for (i = 0; i < pathspec->nr; i++)
+		argv_array_push(&submodule_options,
+				pathspec->items[i].original);
+}
+
+/*
+ * Launch child process to grep contents of a submodule
+ */
+static int grep_submodule_launch(struct grep_opt *opt,
+				 const struct grep_source *gs)
+{
+	struct child_process cp = CHILD_PROCESS_INIT;
+	int status, i;
+	const char *end_of_base;
+	const char *name;
+	struct work_item *w = opt->output_priv;
+
+	end_of_base = strchr(gs->name, ':');
+	if (gs->identifier && end_of_base)
+		name = end_of_base + 1;
+	else
+		name = gs->name;
+
+	prepare_submodule_repo_env(&cp.env_array);
+	argv_array_push(&cp.env_array, GIT_DIR_ENVIRONMENT);
+
+	/* Add super prefix */
+	argv_array_pushf(&cp.args, "--super-prefix=%s%s/",
+			 super_prefix ? super_prefix : "",
+			 name);
+	argv_array_push(&cp.args, "grep");
+
+	/*
+	 * Add basename of parent project
+	 * When performing grep on a tree object the filename is prefixed
+	 * with the object's name: 'tree-name:filename'.  In order to
+	 * provide uniformity of output we want to pass the name of the
+	 * parent project's object name to the submodule so the submodule can
+	 * prefix its output with the parent's name and not its own SHA1.
+	 */
+	if (gs->identifier && end_of_base)
+		argv_array_pushf(&cp.args, "--parent-basename=%.*s",
+				 (int) (end_of_base - gs->name),
+				 gs->name);
+
+	/* Add options */
+	for (i = 0; i < submodule_options.argc; i++) {
+		/*
+		 * If there is a tree identifier for the submodule, add the
+		 * rev after adding the submodule options but before the
+		 * pathspecs.  To do this we listen for the '--' and insert the
+		 * sha1 before pushing the '--' onto the child process argv
+		 * array.
+		 */
+		if (gs->identifier &&
+		    !strcmp("--", submodule_options.argv[i])) {
+			argv_array_push(&cp.args, sha1_to_hex(gs->identifier));
+		}
+
+		argv_array_push(&cp.args, submodule_options.argv[i]);
+	}
+
+	cp.git_cmd = 1;
+	cp.dir = gs->path;
+
+	/*
+	 * Capture output to output buffer and check the return code from the
+	 * child process.  A '0' indicates a hit, a '1' indicates no hit and
+	 * anything else is an error.
+	 */
+	status = capture_command(&cp, &w->out, 0);
+	if (status && (status != 1)) {
+		/* flush the buffer */
+		write_or_die(1, w->out.buf, w->out.len);
+		die("process for submodule '%s' failed with exit code: %d",
+		    gs->name, status);
+	}
+
+	/* invert the return code to make a hit equal to 1 */
+	return !status;
+}
+
+/*
+ * Prep grep structures for a submodule grep
+ * sha1: the sha1 of the submodule or NULL if using the working tree
+ * filename: name of the submodule including tree name of parent
+ * path: location of the submodule
+ */
+static int grep_submodule(struct grep_opt *opt, const unsigned char *sha1,
+			  const char *filename, const char *path)
+{
+	if (!is_submodule_initialized(path))
+		return 0;
+	if (!is_submodule_populated(path)) {
+		/*
+		 * If searching history, check for the presense of the
+		 * submodule's gitdir before skipping the submodule.
+		 */
+		if (sha1) {
+			const struct submodule *sub =
+					submodule_from_path(null_sha1, path);
+			if (sub)
+				path = git_path("modules/%s", sub->name);
+
+			if (!(is_directory(path) && is_git_directory(path)))
+				return 0;
+		} else {
+			return 0;
+		}
+	}
+
+#ifndef NO_PTHREADS
+	if (num_threads) {
+		add_work(opt, GREP_SOURCE_SUBMODULE, filename, path, sha1);
+		return 0;
+	} else
+#endif
+	{
+		struct work_item w;
+		int hit;
+
+		grep_source_init(&w.source, GREP_SOURCE_SUBMODULE,
+				 filename, path, sha1);
+		strbuf_init(&w.out, 0);
+		opt->output_priv = &w;
+		hit = grep_submodule_launch(opt, &w.source);
+
+		write_or_die(1, w.out.buf, w.out.len);
+
+		grep_source_clear(&w.source);
+		strbuf_release(&w.out);
+		return hit;
+	}
+}
+
+static int grep_cache(struct grep_opt *opt, const struct pathspec *pathspec,
+		      int cached)
 {
 	int hit = 0;
 	int nr;
+	struct strbuf name = STRBUF_INIT;
+	int name_base_len = 0;
+	if (super_prefix) {
+		name_base_len = strlen(super_prefix);
+		strbuf_addstr(&name, super_prefix);
+	}
+
 	read_cache();
 
 	for (nr = 0; nr < active_nr; nr++) {
 		const struct cache_entry *ce = active_cache[nr];
-		if (!S_ISREG(ce->ce_mode))
-			continue;
-		if (!ce_path_match(ce, pathspec, NULL))
+		strbuf_setlen(&name, name_base_len);
+		strbuf_addstr(&name, ce->name);
+
+		if (S_ISREG(ce->ce_mode) &&
+		    match_pathspec(pathspec, name.buf, name.len, 0, NULL,
+				   S_ISDIR(ce->ce_mode) ||
+				   S_ISGITLINK(ce->ce_mode))) {
+			/*
+			 * If CE_VALID is on, we assume worktree file and its
+			 * cache entry are identical, even if worktree file has
+			 * been modified, so use cache version instead
+			 */
+			if (cached || (ce->ce_flags & CE_VALID) ||
+			    ce_skip_worktree(ce)) {
+				if (ce_stage(ce) || ce_intent_to_add(ce))
+					continue;
+				hit |= grep_sha1(opt, ce->oid.hash, ce->name,
+						 0, ce->name);
+			} else {
+				hit |= grep_file(opt, ce->name);
+			}
+		} else if (recurse_submodules && S_ISGITLINK(ce->ce_mode) &&
+			   submodule_path_match(pathspec, name.buf, NULL)) {
+			hit |= grep_submodule(opt, NULL, ce->name, ce->name);
+		} else {
 			continue;
-		/*
-		 * If CE_VALID is on, we assume worktree file and its cache entry
-		 * are identical, even if worktree file has been modified, so use
-		 * cache version instead
-		 */
-		if (cached || (ce->ce_flags & CE_VALID) || ce_skip_worktree(ce)) {
-			if (ce_stage(ce) || ce_intent_to_add(ce))
-				continue;
-			hit |= grep_sha1(opt, ce->oid.hash, ce->name, 0,
-					 ce->name);
 		}
-		else
-			hit |= grep_file(opt, ce->name);
+
 		if (ce_stage(ce)) {
 			do {
 				nr++;
 			} while (nr < active_nr &&
 				 !strcmp(ce->name, active_cache[nr]->name));
 			nr--; /* compensate for loop control */
 		}
 		if (hit && opt->status_only)
 			break;
 	}
+
+	strbuf_release(&name);
 	return hit;
 }
 
 static int grep_tree(struct grep_opt *opt, const struct pathspec *pathspec,
 		     struct tree_desc *tree, struct strbuf *base, int tn_len,
 		     int check_attr)
 {
 	int hit = 0;
 	enum interesting match = entry_not_interesting;
 	struct name_entry entry;
 	int old_baselen = base->len;
+	struct strbuf name = STRBUF_INIT;
+	int name_base_len = 0;
+	if (super_prefix) {
+		strbuf_addstr(&name, super_prefix);
+		name_base_len = name.len;
+	}
 
 	while (tree_entry(tree, &entry)) {
 		int te_len = tree_entry_len(&entry);
 
 		if (match != all_entries_interesting) {
-			match = tree_entry_interesting(&entry, base, tn_len, pathspec);
+			strbuf_addstr(&name, base->buf + tn_len);
+			match = tree_entry_interesting(&entry, &name,
+						       0, pathspec);
+			strbuf_setlen(&name, name_base_len);
+
 			if (match == all_entries_not_interesting)
 				break;
 			if (match == entry_not_interesting)
 				continue;
 		}
 
 		strbuf_add(base, entry.path, te_len);
 
 		if (S_ISREG(entry.mode)) {
 			hit |= grep_sha1(opt, entry.oid->hash, base->buf, tn_len,
 					 check_attr ? base->buf + tn_len : NULL);
-		}
-		else if (S_ISDIR(entry.mode)) {
+		} else if (S_ISDIR(entry.mode)) {
 			enum object_type type;
 			struct tree_desc sub;
 			void *data;
 			unsigned long size;
 
 			data = lock_and_read_sha1_file(entry.oid->hash, &type, &size);
