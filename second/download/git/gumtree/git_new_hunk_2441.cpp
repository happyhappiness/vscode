			      config_filename, strerror(errno));
			ret = CONFIG_INVALID_FILE;
			contents = NULL;
			goto out_free;
		}
		close(in_fd);
		in_fd = -1;

		if (chmod(lock->filename.buf, st.st_mode & 07777) < 0) {
			error("chmod on %s failed: %s",
				lock->filename.buf, strerror(errno));
			ret = CONFIG_NO_WRITE;
			goto out_free;
