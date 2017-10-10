 
 	printf("%s", ret);
 	strbuf_release(&sb);
 	return 0;
 }
 
+static int absorb_git_dirs(int argc, const char **argv, const char *prefix)
+{
+	int i;
+	struct pathspec pathspec;
+	struct module_list list = MODULE_LIST_INIT;
+	unsigned flags = ABSORB_GITDIR_RECURSE_SUBMODULES;
+
+	struct option embed_gitdir_options[] = {
+		OPT_STRING(0, "prefix", &prefix,
+			   N_("path"),
+			   N_("path into the working tree")),
+		OPT_BIT(0, "--recursive", &flags, N_("recurse into submodules"),
+			ABSORB_GITDIR_RECURSE_SUBMODULES),
+		OPT_END()
+	};
+
+	const char *const git_submodule_helper_usage[] = {
+		N_("git submodule--helper embed-git-dir [<path>...]"),
+		NULL
+	};
+
+	argc = parse_options(argc, argv, prefix, embed_gitdir_options,
+			     git_submodule_helper_usage, 0);
+
+	gitmodules_config();
+	git_config(submodule_config, NULL);
+
+	if (module_list_compute(argc, argv, prefix, &pathspec, &list) < 0)
+		return 1;
+
+	for (i = 0; i < list.nr; i++)
+		absorb_git_dir_into_superproject(prefix,
+				list.entries[i]->name, flags);
+
+	return 0;
+}
+
+#define SUPPORT_SUPER_PREFIX (1<<0)
+
 struct cmd_struct {
 	const char *cmd;
 	int (*fn)(int, const char **, const char *);
+	unsigned option;
 };
 
 static struct cmd_struct commands[] = {
-	{"list", module_list},
-	{"name", module_name},
-	{"clone", module_clone},
-	{"update-clone", update_clone},
-	{"relative-path", resolve_relative_path},
-	{"resolve-relative-url", resolve_relative_url},
-	{"resolve-relative-url-test", resolve_relative_url_test},
-	{"init", module_init},
-	{"remote-branch", resolve_remote_submodule_branch}
+	{"list", module_list, 0},
+	{"name", module_name, 0},
+	{"clone", module_clone, 0},
+	{"update-clone", update_clone, 0},
+	{"relative-path", resolve_relative_path, 0},
+	{"resolve-relative-url", resolve_relative_url, 0},
+	{"resolve-relative-url-test", resolve_relative_url_test, 0},
+	{"init", module_init, SUPPORT_SUPER_PREFIX},
+	{"remote-branch", resolve_remote_submodule_branch, 0},
+	{"absorb-git-dirs", absorb_git_dirs, SUPPORT_SUPER_PREFIX},
 };
 
 int cmd_submodule__helper(int argc, const char **argv, const char *prefix)
 {
 	int i;
 	if (argc < 2)
 		die(_("submodule--helper subcommand must be "
 		      "called with a subcommand"));
 
-	for (i = 0; i < ARRAY_SIZE(commands); i++)
-		if (!strcmp(argv[1], commands[i].cmd))
+	for (i = 0; i < ARRAY_SIZE(commands); i++) {
+		if (!strcmp(argv[1], commands[i].cmd)) {
+			if (get_super_prefix() &&
+			    !(commands[i].option & SUPPORT_SUPER_PREFIX))
+				die(_("%s doesn't support --super-prefix"),
+				    commands[i].cmd);
 			return commands[i].fn(argc - 1, argv + 1, prefix);
+		}
+	}
 
 	die(_("'%s' is not a valid submodule--helper "
 	      "subcommand"), argv[1]);
 }
