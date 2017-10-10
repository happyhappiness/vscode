 	free(sm_gitdir);
 	free(path);
 	free(p);
 	return 0;
 }
 
+struct submodule_update_clone {
+	/* index into 'list', the list of submodules to look into for cloning */
+	int current;
+	struct module_list list;
+	unsigned warn_if_uninitialized : 1;
+
+	/* update parameter passed via commandline */
+	struct submodule_update_strategy update;
+
+	/* configuration parameters which are passed on to the children */
+	int quiet;
+	const char *reference;
+	const char *depth;
+	const char *recursive_prefix;
+	const char *prefix;
+
+	/* Machine-readable status lines to be consumed by git-submodule.sh */
+	struct string_list projectlines;
+
+	/* If we want to stop as fast as possible and return an error */
+	unsigned quickstop : 1;
+};
+#define SUBMODULE_UPDATE_CLONE_INIT {0, MODULE_LIST_INIT, 0, \
+	SUBMODULE_UPDATE_STRATEGY_INIT, 0, NULL, NULL, NULL, NULL, \
+	STRING_LIST_INIT_DUP, 0}
+
+
+static void next_submodule_warn_missing(struct submodule_update_clone *suc,
+		struct strbuf *out, const char *displaypath)
+{
+	/*
+	 * Only mention uninitialized submodules when their
+	 * paths have been specified.
+	 */
+	if (suc->warn_if_uninitialized) {
+		strbuf_addf(out,
+			_("Submodule path '%s' not initialized"),
+			displaypath);
+		strbuf_addch(out, '\n');
+		strbuf_addstr(out,
+			_("Maybe you want to use 'update --init'?"));
+		strbuf_addch(out, '\n');
+	}
+}
+
+/**
+ * Determine whether 'ce' needs to be cloned. If so, prepare the 'child' to
+ * run the clone. Returns 1 if 'ce' needs to be cloned, 0 otherwise.
+ */
+static int prepare_to_clone_next_submodule(const struct cache_entry *ce,
+					   struct child_process *child,
+					   struct submodule_update_clone *suc,
+					   struct strbuf *out)
+{
+	const struct submodule *sub = NULL;
+	struct strbuf displaypath_sb = STRBUF_INIT;
+	struct strbuf sb = STRBUF_INIT;
+	const char *displaypath = NULL;
+	char *url = NULL;
+	int needs_cloning = 0;
+
+	if (ce_stage(ce)) {
+		if (suc->recursive_prefix)
+			strbuf_addf(&sb, "%s/%s", suc->recursive_prefix, ce->name);
+		else
+			strbuf_addf(&sb, "%s", ce->name);
+		strbuf_addf(out, _("Skipping unmerged submodule %s"), sb.buf);
+		strbuf_addch(out, '\n');
+		goto cleanup;
+	}
+
+	sub = submodule_from_path(null_sha1, ce->name);
+
+	if (suc->recursive_prefix)
+		displaypath = relative_path(suc->recursive_prefix,
+					    ce->name, &displaypath_sb);
+	else
+		displaypath = ce->name;
+
+	if (!sub) {
+		next_submodule_warn_missing(suc, out, displaypath);
+		goto cleanup;
+	}
+
+	if (suc->update.type == SM_UPDATE_NONE
+	    || (suc->update.type == SM_UPDATE_UNSPECIFIED
+		&& sub->update_strategy.type == SM_UPDATE_NONE)) {
+		strbuf_addf(out, _("Skipping submodule '%s'"), displaypath);
+		strbuf_addch(out, '\n');
+		goto cleanup;
+	}
+
+	/*
+	 * Looking up the url in .git/config.
+	 * We must not fall back to .gitmodules as we only want
+	 * to process configured submodules.
+	 */
+	strbuf_reset(&sb);
+	strbuf_addf(&sb, "submodule.%s.url", sub->name);
+	git_config_get_string(sb.buf, &url);
+	if (!url) {
+		next_submodule_warn_missing(suc, out, displaypath);
+		goto cleanup;
+	}
+
+	strbuf_reset(&sb);
+	strbuf_addf(&sb, "%s/.git", ce->name);
+	needs_cloning = !file_exists(sb.buf);
+
+	strbuf_reset(&sb);
+	strbuf_addf(&sb, "%06o %s %d %d\t%s\n", ce->ce_mode,
+			sha1_to_hex(ce->sha1), ce_stage(ce),
+			needs_cloning, ce->name);
+	string_list_append(&suc->projectlines, sb.buf);
+
+	if (!needs_cloning)
+		goto cleanup;
+
+	child->git_cmd = 1;
+	child->no_stdin = 1;
+	child->stdout_to_stderr = 1;
+	child->err = -1;
+	argv_array_push(&child->args, "submodule--helper");
+	argv_array_push(&child->args, "clone");
+	if (suc->quiet)
+		argv_array_push(&child->args, "--quiet");
+	if (suc->prefix)
+		argv_array_pushl(&child->args, "--prefix", suc->prefix, NULL);
+	argv_array_pushl(&child->args, "--path", sub->path, NULL);
+	argv_array_pushl(&child->args, "--name", sub->name, NULL);
+	argv_array_pushl(&child->args, "--url", url, NULL);
+	if (suc->reference)
+		argv_array_push(&child->args, suc->reference);
+	if (suc->depth)
+		argv_array_push(&child->args, suc->depth);
+
+cleanup:
+	free(url);
+	strbuf_reset(&displaypath_sb);
+	strbuf_reset(&sb);
+
+	return needs_cloning;
+}
+
+static int update_clone_get_next_task(struct child_process *child,
+				      struct strbuf *err,
+				      void *suc_cb,
+				      void **void_task_cb)
+{
+	struct submodule_update_clone *suc = suc_cb;
+
+	for (; suc->current < suc->list.nr; suc->current++) {
+		const struct cache_entry *ce = suc->list.entries[suc->current];
+		if (prepare_to_clone_next_submodule(ce, child, suc, err)) {
+			suc->current++;
+			return 1;
+		}
+	}
+	return 0;
+}
+
+static int update_clone_start_failure(struct strbuf *err,
+				      void *suc_cb,
+				      void *void_task_cb)
+{
+	struct submodule_update_clone *suc = suc_cb;
+	suc->quickstop = 1;
+	return 1;
+}
+
+static int update_clone_task_finished(int result,
+				      struct strbuf *err,
+				      void *suc_cb,
+				      void *void_task_cb)
+{
+	struct submodule_update_clone *suc = suc_cb;
+
+	if (!result)
+		return 0;
+
+	suc->quickstop = 1;
+	return 1;
+}
+
+static int update_clone(int argc, const char **argv, const char *prefix)
+{
+	const char *update = NULL;
+	int max_jobs = -1;
+	struct string_list_item *item;
+	struct pathspec pathspec;
+	struct submodule_update_clone suc = SUBMODULE_UPDATE_CLONE_INIT;
+
+	struct option module_update_clone_options[] = {
+		OPT_STRING(0, "prefix", &prefix,
+			   N_("path"),
+			   N_("path into the working tree")),
+		OPT_STRING(0, "recursive-prefix", &suc.recursive_prefix,
+			   N_("path"),
+			   N_("path into the working tree, across nested "
+			      "submodule boundaries")),
+		OPT_STRING(0, "update", &update,
+			   N_("string"),
+			   N_("rebase, merge, checkout or none")),
+		OPT_STRING(0, "reference", &suc.reference, N_("repo"),
+			   N_("reference repository")),
+		OPT_STRING(0, "depth", &suc.depth, "<depth>",
+			   N_("Create a shallow clone truncated to the "
+			      "specified number of revisions")),
+		OPT_INTEGER('j', "jobs", &max_jobs,
+			    N_("parallel jobs")),
+		OPT__QUIET(&suc.quiet, N_("don't print cloning progress")),
+		OPT_END()
+	};
+
+	const char *const git_submodule_helper_usage[] = {
+		N_("git submodule--helper update_clone [--prefix=<path>] [<path>...]"),
+		NULL
+	};
+	suc.prefix = prefix;
+
+	argc = parse_options(argc, argv, prefix, module_update_clone_options,
+			     git_submodule_helper_usage, 0);
+
+	if (update)
+		if (parse_submodule_update_strategy(update, &suc.update) < 0)
+			die(_("bad value for update parameter"));
+
+	if (module_list_compute(argc, argv, prefix, &pathspec, &suc.list) < 0)
+		return 1;
+
+	if (pathspec.nr)
+		suc.warn_if_uninitialized = 1;
+
+	/* Overlay the parsed .gitmodules file with .git/config */
+	gitmodules_config();
+	git_config(submodule_config, NULL);
+
+	if (max_jobs < 0)
+		max_jobs = parallel_submodules();
+
+	run_processes_parallel(max_jobs,
+			       update_clone_get_next_task,
+			       update_clone_start_failure,
+			       update_clone_task_finished,
+			       &suc);
+
+	/*
+	 * We saved the output and put it out all at once now.
+	 * That means:
+	 * - the listener does not have to interleave their (checkout)
+	 *   work with our fetching.  The writes involved in a
+	 *   checkout involve more straightforward sequential I/O.
+	 * - the listener can avoid doing any work if fetching failed.
+	 */
+	if (suc.quickstop)
+		return 1;
+
+	for_each_string_list_item(item, &suc.projectlines)
+		utf8_fprintf(stdout, "%s", item->string);
+
+	return 0;
+}
+
+static int resolve_relative_path(int argc, const char **argv, const char *prefix)
+{
+	struct strbuf sb = STRBUF_INIT;
+	if (argc != 3)
+		die("submodule--helper relative_path takes exactly 2 arguments, got %d", argc);
+
+	printf("%s", relative_path(argv[1], argv[2], &sb));
+	strbuf_release(&sb);
+	return 0;
+}
+
 struct cmd_struct {
 	const char *cmd;
 	int (*fn)(int, const char **, const char *);
 };
 
 static struct cmd_struct commands[] = {
 	{"list", module_list},
 	{"name", module_name},
 	{"clone", module_clone},
+	{"update-clone", update_clone},
+	{"relative-path", resolve_relative_path},
+	{"resolve-relative-url", resolve_relative_url},
+	{"resolve-relative-url-test", resolve_relative_url_test},
+	{"init", module_init}
 };
 
 int cmd_submodule__helper(int argc, const char **argv, const char *prefix)
 {
 	int i;
 	if (argc < 2)
-		die(_("fatal: submodule--helper subcommand must be "
+		die(_("submodule--helper subcommand must be "
 		      "called with a subcommand"));
 
 	for (i = 0; i < ARRAY_SIZE(commands); i++)
 		if (!strcmp(argv[1], commands[i].cmd))
 			return commands[i].fn(argc - 1, argv + 1, prefix);
 
-	die(_("fatal: '%s' is not a valid submodule--helper "
+	die(_("'%s' is not a valid submodule--helper "
 	      "subcommand"), argv[1]);
 }
