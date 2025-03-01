 
 	if (argc > 0) {
 		repo = argv[0];
 		set_refspecs(argv + 1, argc - 1, repo);
 	}
 
-	rc = do_push(repo, flags);
+	for_each_string_list_item(item, &push_options)
+		if (strchr(item->string, '\n'))
+			die(_("push options must not have new line characters"));
+
+	rc = do_push(repo, flags, &push_options);
 	if (rc == -1)
 		usage_with_options(push_usage, options);
 	else
 		return rc;
 }
