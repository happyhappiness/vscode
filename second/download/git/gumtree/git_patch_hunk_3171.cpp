 	cb_data.keep = &known_remotes;
 
 	if (argc != 2)
 		usage_with_options(builtin_remote_rm_usage, options);
 
 	remote = remote_get(argv[1]);
-	if (!remote)
+	if (!remote_is_configured(remote))
 		die(_("No such remote: %s"), argv[1]);
 
 	known_remotes.to_delete = remote;
 	for_each_remote(add_known_remote, &known_remotes);
 
 	read_branches();
