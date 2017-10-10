 		}
 	if (omit_values &&
 	    !(actions == ACTION_LIST || actions == ACTION_GET_REGEXP)) {
 		error("--name-only is only applicable to --list or --get-regexp");
 		usage_with_options(builtin_config_usage, builtin_config_options);
 	}
+
+	if (show_origin && !(actions &
+		(ACTION_GET|ACTION_GET_ALL|ACTION_GET_REGEXP|ACTION_LIST))) {
+		error("--show-origin is only applicable to --get, --get-all, "
+			  "--get-regexp, and --list.");
+		usage_with_options(builtin_config_usage, builtin_config_options);
+	}
+
 	if (actions == ACTION_LIST) {
 		check_argc(argc, 0, 0);
 		if (git_config_with_options(show_all_config, NULL,
 					    &given_config_source,
 					    respect_includes) < 0) {
 			if (given_config_source.file)
