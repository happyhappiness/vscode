 
 	prefix = setup_git_directory();
 	git_config(git_default_config, NULL);
 	for (i = 1; i < argc; i++) {
 		const char *arg = argv[i];
 
+		if (!strcmp(arg, "--git-path")) {
+			if (!argv[i + 1])
+				die("--git-path requires an argument");
+			puts(git_path("%s", argv[i + 1]));
+			i++;
+			continue;
+		}
 		if (as_is) {
 			if (show_file(arg, output_prefix) && as_is < 2)
 				verify_filename(prefix, arg, 0);
 			continue;
 		}
 		if (!strcmp(arg,"-n")) {
