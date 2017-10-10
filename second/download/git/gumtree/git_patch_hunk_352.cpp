 		int ret;
 		check_write();
 		check_argc(argc, 2, 2);
 		value = normalize_value(argv[0], argv[1]);
 		ret = git_config_set_in_file_gently(given_config_source.file, argv[0], value);
 		if (ret == CONFIG_NOTHING_SET)
-			error("cannot overwrite multiple values with a single value\n"
-			"       Use a regexp, --add or --replace-all to change %s.", argv[0]);
+			error(_("cannot overwrite multiple values with a single value\n"
+			"       Use a regexp, --add or --replace-all to change %s."), argv[0]);
 		return ret;
 	}
 	else if (actions == ACTION_SET_ALL) {
 		check_write();
 		check_argc(argc, 2, 3);
 		value = normalize_value(argv[0], argv[1]);
