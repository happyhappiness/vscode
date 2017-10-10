			die("not in a git directory");
		if (given_config_source.use_stdin)
			die("editing stdin is not supported");
		if (given_config_source.blob)
			die("editing blobs is not supported");
		git_config(git_default_config, NULL);
		config_file = given_config_source.file ?
				xstrdup(given_config_source.file) :
				git_pathdup("config");
		if (use_global_config) {
			int fd = open(config_file, O_CREAT | O_EXCL | O_WRONLY, 0666);
			if (fd >= 0) {
				char *content = default_user_config();
				write_str_in_full(fd, content);
				free(content);
