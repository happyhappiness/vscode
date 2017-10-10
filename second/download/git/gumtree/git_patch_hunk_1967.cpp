 					  given_config_source.file);
 			else
 				die("error processing config file(s)");
 		}
 	}
 	else if (actions == ACTION_EDIT) {
-		const char *config_file = given_config_source.file ?
-			given_config_source.file : git_path("config");
+		char *config_file;
+
 		check_argc(argc, 0, 0);
 		if (!given_config_source.file && nongit)
 			die("not in a git directory");
 		if (given_config_source.use_stdin)
 			die("editing stdin is not supported");
 		if (given_config_source.blob)
 			die("editing blobs is not supported");
 		git_config(git_default_config, NULL);
+		config_file = xstrdup(given_config_source.file ?
+				      given_config_source.file : git_path("config"));
 		if (use_global_config) {
 			int fd = open(config_file, O_CREAT | O_EXCL | O_WRONLY, 0666);
 			if (fd) {
 				char *content = default_user_config();
 				write_str_in_full(fd, content);
 				free(content);
 				close(fd);
 			}
 			else if (errno != EEXIST)
 				die_errno(_("cannot create configuration file %s"), config_file);
 		}
 		launch_editor(config_file, NULL, NULL);
+		free(config_file);
 	}
 	else if (actions == ACTION_SET) {
 		int ret;
 		check_write();
 		check_argc(argc, 2, 2);
 		value = normalize_value(argv[0], argv[1]);
