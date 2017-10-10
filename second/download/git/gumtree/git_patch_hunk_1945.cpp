 		if (ret < 0)
 			return ret;
 		if (ret == 0)
 			die("No such section!");
 	}
 	else if (actions == ACTION_GET_COLOR) {
-		get_color(argv[0]);
+		check_argc(argc, 1, 2);
+		get_color(argv[0], argv[1]);
 	}
 	else if (actions == ACTION_GET_COLORBOOL) {
-		if (argc == 1)
-			color_stdout_is_tty = git_config_bool("command line", argv[0]);
-		return get_colorbool(argc != 0);
+		check_argc(argc, 1, 2);
+		if (argc == 2)
+			color_stdout_is_tty = git_config_bool("command line", argv[1]);
+		return get_colorbool(argv[0], argc == 2);
 	}
 
 	return 0;
 }
