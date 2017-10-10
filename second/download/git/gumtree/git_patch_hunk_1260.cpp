 			  "--get-regexp, and --list.");
 		usage_with_options(builtin_config_usage, builtin_config_options);
 	}
 
 	if (actions == ACTION_LIST) {
 		check_argc(argc, 0, 0);
-		if (git_config_with_options(show_all_config, NULL,
-					    &given_config_source,
-					    &config_options) < 0) {
+		if (config_with_options(show_all_config, NULL,
+					&given_config_source,
+					&config_options) < 0) {
 			if (given_config_source.file)
 				die_errno("unable to read config file '%s'",
 					  given_config_source.file);
 			else
 				die("error processing config file(s)");
 		}
