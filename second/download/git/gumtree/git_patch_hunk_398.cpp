 		result = remove_cmd(argc, argv, prefix);
 	else if (!strcmp(argv[0], "prune"))
 		result = prune(argc, argv, prefix);
 	else if (!strcmp(argv[0], "get-ref"))
 		result = get_ref(argc, argv, prefix);
 	else {
-		result = error(_("Unknown subcommand: %s"), argv[0]);
+		result = error(_("unknown subcommand: %s"), argv[0]);
 		usage_with_options(git_notes_usage, options);
 	}
 
 	return result ? 1 : 0;
 }
