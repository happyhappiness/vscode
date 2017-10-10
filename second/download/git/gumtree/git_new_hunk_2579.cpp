			contents = NULL;
			goto out_free;
		}
		close(in_fd);
		in_fd = -1;

		if (chmod(get_lock_file_path(lock), st.st_mode & 07777) < 0) {
			error("chmod on %s failed: %s",
			      get_lock_file_path(lock), strerror(errno));
			ret = CONFIG_NO_WRITE;
			goto out_free;
		}

		if (store.seen == 0)
			store.seen = 1;
