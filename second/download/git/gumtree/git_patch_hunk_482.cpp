 		if ((p->option & (RUN_SETUP | RUN_SETUP_GENTLY)) &&
 		    startup_info->have_repository) /* get_git_dir() may set up repo, avoid that */
 			trace_repo_setup(prefix);
 	}
 	commit_pager_choice();
 
+	if (!help && get_super_prefix()) {
+		if (!(p->option & SUPPORT_SUPER_PREFIX))
+			die("%s doesn't support --super-prefix", p->cmd);
+		if (prefix)
+			die("can't use --super-prefix from a subdirectory");
+	}
+
 	if (!help && p->option & NEED_WORK_TREE)
 		setup_work_tree();
 
 	trace_argv_printf(argv, "trace: built-in: git");
 
 	status = p->fn(argc, argv, prefix);
