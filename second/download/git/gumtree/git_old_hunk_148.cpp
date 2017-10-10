	int ret = 0, remove = 0;
	char *filename_buf = NULL;
	struct lock_file *lock;
	int out_fd;
	char buf[1024];
	FILE *config_file;

	if (new_name && !section_name_is_ok(new_name)) {
		ret = error("invalid section name: %s", new_name);
		goto out;
	}

