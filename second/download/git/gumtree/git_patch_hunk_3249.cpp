 				if (config_fetch_recurse_submodules == RECURSE_SUBMODULES_ON_DEMAND) {
 					if (!unsorted_string_list_lookup(&changed_submodule_paths, ce->name))
 						continue;
 					default_argv = "on-demand";
 				}
 			}
-		} else if (command_line_option == RECURSE_SUBMODULES_ON_DEMAND) {
+		} else if (spf->command_line_option == RECURSE_SUBMODULES_ON_DEMAND) {
 			if (!unsorted_string_list_lookup(&changed_submodule_paths, ce->name))
 				continue;
 			default_argv = "on-demand";
 		}
 
-		strbuf_addf(&submodule_path, "%s/%s", work_tree, ce->name);
+		strbuf_addf(&submodule_path, "%s/%s", spf->work_tree, ce->name);
 		strbuf_addf(&submodule_git_dir, "%s/.git", submodule_path.buf);
-		strbuf_addf(&submodule_prefix, "%s%s/", prefix, ce->name);
+		strbuf_addf(&submodule_prefix, "%s%s/", spf->prefix, ce->name);
 		git_dir = read_gitfile(submodule_git_dir.buf);
 		if (!git_dir)
 			git_dir = submodule_git_dir.buf;
 		if (is_directory(git_dir)) {
-			if (!quiet)
-				printf("Fetching submodule %s%s\n", prefix, ce->name);
-			cp.dir = submodule_path.buf;
-			argv_array_push(&argv, default_argv);
-			argv_array_push(&argv, "--submodule-prefix");
-			argv_array_push(&argv, submodule_prefix.buf);
-			cp.argv = argv.argv;
-			if (run_command(&cp))
-				result = 1;
-			argv_array_pop(&argv);
-			argv_array_pop(&argv);
-			argv_array_pop(&argv);
+			child_process_init(cp);
+			cp->dir = strbuf_detach(&submodule_path, NULL);
+			cp->env = local_repo_env;
+			cp->git_cmd = 1;
+			if (!spf->quiet)
+				strbuf_addf(err, "Fetching submodule %s%s\n",
+					    spf->prefix, ce->name);
+			argv_array_init(&cp->args);
+			argv_array_pushv(&cp->args, spf->args.argv);
+			argv_array_push(&cp->args, default_argv);
+			argv_array_push(&cp->args, "--submodule-prefix");
+			argv_array_push(&cp->args, submodule_prefix.buf);
+			ret = 1;
 		}
 		strbuf_release(&submodule_path);
 		strbuf_release(&submodule_git_dir);
 		strbuf_release(&submodule_prefix);
+		if (ret) {
+			spf->count++;
+			return 1;
+		}
 	}
-	argv_array_clear(&argv);
+	return 0;
+}
+
+static int fetch_start_failure(struct strbuf *err,
+			       void *cb, void *task_cb)
+{
+	struct submodule_parallel_fetch *spf = cb;
+
+	spf->result = 1;
+
+	return 0;
+}
+
+static int fetch_finish(int retvalue, struct strbuf *err,
+			void *cb, void *task_cb)
+{
+	struct submodule_parallel_fetch *spf = cb;
+
+	if (retvalue)
+		spf->result = 1;
+
+	return 0;
+}
+
+int fetch_populated_submodules(const struct argv_array *options,
+			       const char *prefix, int command_line_option,
+			       int quiet, int max_parallel_jobs)
+{
+	int i;
+	struct submodule_parallel_fetch spf = SPF_INIT;
+
+	spf.work_tree = get_git_work_tree();
+	spf.command_line_option = command_line_option;
+	spf.quiet = quiet;
+	spf.prefix = prefix;
+
+	if (!spf.work_tree)
+		goto out;
+
+	if (read_cache() < 0)
+		die("index file corrupt");
+
+	argv_array_push(&spf.args, "fetch");
+	for (i = 0; i < options->argc; i++)
+		argv_array_push(&spf.args, options->argv[i]);
+	argv_array_push(&spf.args, "--recurse-submodules-default");
+	/* default value, "--submodule-prefix" and its value are added later */
+
+	calculate_changed_submodule_paths();
+	run_processes_parallel(max_parallel_jobs,
+			       get_next_submodule,
+			       fetch_start_failure,
+			       fetch_finish,
+			       &spf);
+
+	argv_array_clear(&spf.args);
 out:
 	string_list_clear(&changed_submodule_paths, 1);
-	return result;
+	return spf.result;
 }
 
 unsigned is_submodule_modified(const char *path, int ignore_untracked)
 {
 	ssize_t len;
 	struct child_process cp = CHILD_PROCESS_INIT;
