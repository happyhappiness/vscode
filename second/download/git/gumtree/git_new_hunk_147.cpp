		fstat(in_fd, &st);
		contents_sz = xsize_t(st.st_size);
		contents = xmmap(NULL, contents_sz, PROT_READ,
			MAP_PRIVATE, in_fd, 0);
		close(in_fd);

		if (chmod(lock->filename, st.st_mode & 07777) < 0) {
			error("chmod on %s failed: %s",
				lock->filename, strerror(errno));
			ret = CONFIG_NO_WRITE;
			goto out_free;
		}

		if (store.seen == 0)
			store.seen = 1;

		for (i = 0, copy_begin = 0; i < store.seen; i++) {
			if (store.offset[i] == 0) {
				store.offset[i] = copy_end = contents_sz;
