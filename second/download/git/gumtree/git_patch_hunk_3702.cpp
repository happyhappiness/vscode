 	ac = parse_options(ac, av, prefix, options, worktree_usage, 0);
 	if (!!opts.detach + !!opts.new_branch + !!new_branch_force > 1)
 		die(_("-b, -B, and --detach are mutually exclusive"));
 	if (ac < 1 || ac > 2)
 		usage_with_options(worktree_usage, options);
 
-	path = prefix ? prefix_filename(prefix, strlen(prefix), av[0]) : av[0];
+	path = prefix_filename(prefix, strlen(prefix), av[0]);
 	branch = ac < 2 ? "HEAD" : av[1];
 
+	if (!strcmp(branch, "-"))
+		branch = "@{-1}";
+
 	opts.force_new_branch = !!new_branch_force;
 	if (opts.force_new_branch) {
 		struct strbuf symref = STRBUF_INIT;
 
 		opts.new_branch = new_branch_force;
 
