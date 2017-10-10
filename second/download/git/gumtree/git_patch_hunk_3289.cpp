 		NULL
 	};
 
 	argc = parse_options(argc, argv, prefix, module_clone_options,
 			     git_submodule_helper_usage, 0);
 
+	if (!path || !*path)
+		die(_("submodule--helper: unspecified or empty --path"));
+
 	strbuf_addf(&sb, "%s/modules/%s", get_git_dir(), name);
-	sm_gitdir = strbuf_detach(&sb, NULL);
+	sm_gitdir = xstrdup(absolute_path(sb.buf));
+	strbuf_reset(&sb);
+
+	if (!is_absolute_path(path)) {
+		strbuf_addf(&sb, "%s/%s", get_git_work_tree(), path);
+		path = strbuf_detach(&sb, NULL);
+	} else
+		path = xstrdup(path);
 
 	if (!file_exists(sm_gitdir)) {
 		if (safe_create_leading_directories_const(sm_gitdir) < 0)
 			die(_("could not create directory '%s'"), sm_gitdir);
 		if (clone_submodule(path, sm_gitdir, url, depth, reference, quiet))
 			die(_("clone of '%s' into submodule path '%s' failed"),
