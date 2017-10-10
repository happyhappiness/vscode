			die("editing blobs is not supported");
		git_config(git_default_config, NULL);
		config_file = xstrdup(given_config_source.file ?
				      given_config_source.file : git_path("config"));
		if (use_global_config) {
			int fd = open(config_file, O_CREAT | O_EXCL | O_WRONLY, 0666);
			if (fd) {
				char *content = default_user_config();
				write_str_in_full(fd, content);
				free(content);
				close(fd);
			}
			else if (errno != EEXIST)
