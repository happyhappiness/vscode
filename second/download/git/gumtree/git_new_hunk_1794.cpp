		fstat(in_fd, &st);
		contents_sz = xsize_t(st.st_size);
		contents = xmmap(NULL, contents_sz, PROT_READ,
			MAP_PRIVATE, in_fd, 0);
		close(in_fd);

		if (chmod(lock->filename.buf, st.st_mode & 07777) < 0) {
			error("chmod on %s failed: %s",
				lock->filename.buf, strerror(errno));
			ret = CONFIG_NO_WRITE;
			goto out_free;
		}

		if (store.seen == 0)
			store.seen = 1;
