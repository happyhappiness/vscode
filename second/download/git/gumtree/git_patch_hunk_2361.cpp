 
 	argc = parse_options(argc, (const char **)argv, NULL, options, usage, 0);
 	if (argc != 1)
 		usage_with_options(usage, options);
 	op = argv[0];
 
-	if (!file)
-		file = expand_user_path("~/.git-credentials");
-	if (!file)
+	if (file) {
+		string_list_append(&fns, file);
+	} else {
+		if ((file = expand_user_path("~/.git-credentials")))
+			string_list_append_nodup(&fns, file);
+		file = xdg_config_home("credentials");
+		if (file)
+			string_list_append_nodup(&fns, file);
+	}
+	if (!fns.nr)
 		die("unable to set up default path; use --file");
 
 	if (credential_read(&c, stdin) < 0)
 		die("unable to read credential");
 
 	if (!strcmp(op, "get"))
-		lookup_credential(file, &c);
+		lookup_credential(&fns, &c);
 	else if (!strcmp(op, "erase"))
-		remove_credential(file, &c);
+		remove_credential(&fns, &c);
 	else if (!strcmp(op, "store"))
-		store_credential(file, &c);
+		store_credential(&fns, &c);
 	else
 		; /* Ignore unknown operation. */
 
+	string_list_clear(&fns, 0);
 	return 0;
 }
